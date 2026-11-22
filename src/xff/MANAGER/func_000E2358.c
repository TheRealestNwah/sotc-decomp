typedef struct { int addr; int id; int pad8; } Imp;
typedef struct { char pad0[0x18]; int nimp; Imp *imp; } ModHdr;
typedef struct { char pad0[4]; int id; } ModId;
typedef struct Sheet Sheet;
typedef struct { char pad0[0x40]; Sheet *head; } SheetMgr;
struct Sheet {
    int **code;
    char pad4[0x34];
    void *mod;
    SheetMgr *mgr;
    char pad40[8];
    char grp[0xC];
    Sheet *mgrNext;
    Sheet *next;
    Sheet *prev;
};

extern Sheet *D_00139F18;
extern int DldSysUndefSymbol;
extern char RO_00141BA0[];
extern Sheet **isysGroupForFirst(void *, int);
extern Sheet **isysGroupForNext(Sheet **, int);
extern void isysGroupForExit(Sheet *, int);
extern void isysDeleteGroupAllObj(void *);
extern void iosJumpRecoverPoint(const char *, ...);
extern void AddObjectManagerSheetWorkSize(int);
extern int isysGetModuleObjMallocSize(Sheet *);
extern void isysFlushModuleObj(Sheet *);

/* Unloads a sheet: unlinks it from the pending list, queues the sheets of its group and
 * points their imports from it at DldSysUndefSymbol, then unlinks it from its manager and
 * frees its work size. */
static void func_000E2358(Sheet *s)
{
    Sheet *prev;
    Sheet *o;
    Sheet **it;
    Sheet *p;
    SheetMgr *mgr;

    if (s->prev != 0) {
        if (D_00139F18 != s) {
            if ((s->prev->next = s->next) != 0)
                s->next->prev = s->prev;
        } else {
            D_00139F18 = s->next;
            if (s->next != 0)
                s->next->prev = (Sheet *)-1;
        }
        s->next = 0;
        s->prev = 0;
    }
    s->prev = (Sheet *)-1;
    o = 0;
    for (it = isysGroupForFirst(s->grp, 0); it != 0; it = isysGroupForNext(it, 0)) {
        ModHdr *h;
        Imp *im;
        int n;
        int id;
        int j;

        o = *it;
        if (o->prev == 0) {
            o->prev = (Sheet *)-1;
            o->next = D_00139F18;
            if (D_00139F18 != 0)
                (*(Sheet *volatile *)&D_00139F18)->prev = o;
            D_00139F18 = o;
        }
        h = o->mod;
        n = h->nimp;
        id = ((ModId *)s->mod)->id;
        im = h->imp;
        for (j = 0; j < n; j++) {
            if (im[j].id == id)
                im[j].addr = DldSysUndefSymbol;
        }
    }
    if (o != 0)
        isysGroupForExit(o, 0);
    isysDeleteGroupAllObj(s->grp);
    prev = 0;
    mgr = s->mgr;
    for (p = mgr->head; p != 0 && s != p; p = p->mgrNext)
        prev = p;
    if (p == 0)
        iosJumpRecoverPoint(RO_00141BA0);
    if (prev != 0)
        prev->mgrNext = s->mgrNext;
    else
        mgr->head = s->mgrNext;
    AddObjectManagerSheetWorkSize(-((*s->code[-1] & 0xFFFFFF) << 2));
    AddObjectManagerSheetWorkSize(-isysGetModuleObjMallocSize(s));
    isysFlushModuleObj(s);
}
