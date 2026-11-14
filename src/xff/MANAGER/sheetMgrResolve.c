/* Parked: 159 diffs (words shifted by two). Structure matches; original computes the sheetFsLanguageCode address once (lui a2) and keeps next-sheet in a2. */
#ifdef NONMATCHING
extern void *DldSysUndefSymbol;
extern int sheetFsLanguageCode;
extern void *D_00139F14;
extern void *D_00139F18;
extern long iosGetTCount(void);
extern void iosGetSecondFromTCount(long);
extern int isysSearchSymbol(void *, int, void *);
extern void *isysGroupForFirst(void *, int);
extern void *isysGroupForNext(void *, int);
extern void isysGroupForExit(void *, int);
extern void isysAddGroupWithLinkParam(void *, void *, int, int);
extern int isysResolveOneModuleObj(void *);
extern void isysResolveAllProgramModule(void);

typedef struct Target {
    char pad0[0x14];
    char *group;
} Target;

typedef struct {
    Target *target;
    int name;
    unsigned int pad : 10;
    unsigned int once : 1;
    unsigned int lang : 4;
    unsigned int rest : 17;
} Entry;

typedef struct {
    char pad0[0x18];
    int count;
    Entry *entries;
} Table;

typedef struct Sheet {
    char pad0[0x38];
    Table *table;
    char pad3C[8];
    unsigned int pad44 : 19;
    unsigned int always : 1;
    unsigned int rest44 : 12;
    char pad48[0x10];
    struct Sheet *next;
    struct Sheet *prev;
} Sheet;

typedef struct Module {
    char pad0[0x44];
    struct Module *next;
    struct Module *prev;
} Module;

void sheetMgrResolve(int all)
{
    Sheet *s = (Sheet *)D_00139F18;
    Module *m;

    if (s != 0) {
        do {
            int i;
            int unresolved = 0;
            Sheet *next = s->next;
            Table *t = s->table;
            Entry *e = t->entries;
            long start = iosGetTCount();

            for (i = 0; i < t->count; i++, e++) {
                if (e->name != 0 && (e->lang == 0 || e->lang == sheetFsLanguageCode)) {
                    if (isysSearchSymbol(e, e->name, &sheetFsLanguageCode) == 0) {
                        e->target = DldSysUndefSymbol;
                        unresolved++;
                        if (!s->always && !e->once)
                            __asm__ __volatile__("break 0");
                    } else if (s->always || e->once) {
                        int found = 0;
                        void *g = 0;
                        void *head = e->target->group + 0x48;
                        int *n = isysGroupForFirst(head, 0);
                        while (n != 0) {
                            g = *(void **)n;
                            if (s == g) {
                                found = 1;
                                break;
                            }
                            n = isysGroupForNext(n, 0);
                        }
                        if (g != 0)
                            isysGroupForExit(g, 0);
                        if (found == 0)
                            isysAddGroupWithLinkParam(s, head, 0, 0);
                    }
                }
            }
            if (unresolved == 0 && s->prev != 0) {
                if (D_00139F18 == s) {
                    D_00139F18 = s->next;
                    if (s->next != 0)
                        s->next->prev = (Sheet *)-1;
                } else {
                    s->prev->next = s->next;
                    if (s->next != 0)
                        s->next->prev = s->prev;
                }
                s->prev = 0;
                s->next = 0;
            }
            s = next;
            iosGetSecondFromTCount(iosGetTCount() - start);
        } while (s != 0);
    }
    m = (Module *)D_00139F14;
    while (m != 0) {
        Module *nm = m->next;
        if (isysResolveOneModuleObj(m) == 0 && m->prev != 0) {
            if (D_00139F14 == m) {
                D_00139F14 = m->next;
                if (m->next != 0)
                    m->next->prev = (Module *)-1;
            } else {
                m->prev->next = m->next;
                if (m->next != 0)
                    m->next->prev = m->prev;
            }
            m->prev = 0;
            m->next = 0;
        }
        m = nm;
    }
    if (all != 0)
        isysResolveAllProgramModule();
}
#endif
