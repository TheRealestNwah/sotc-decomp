/* Parked attempt: 4 words differ (the Original loads info->undef after the
 * undefs store instead of right after the call). */
#ifdef NONMATCHING
typedef struct {
    int name;
    char pad4[9];
    unsigned char defined;
    unsigned short section;
} Sym;

typedef struct {
    int hash;
    Sym *sym4;
    Sym *sym8;
    int unkC;
} SymEntry;

typedef struct {
    int heap;
    char pad4[8];
    unsigned char first;
    char padD[0xF];
    int numUndef;
    int *undef;
    int numSyms;
    Sym *syms;
    char *strtab;
} ModInfo;

typedef struct {
    unsigned int rest : 29;
    unsigned int c : 1;
    unsigned int b : 1;
    int a : 1;
} ModFlags;

typedef struct {
    int heap;
    char pad4[0x18];
    ModInfo *info;
    int unk20;
    SymEntry *defs;
    SymEntry *undefs;
    ModFlags flags;
} ModObj;

extern char B_00054398[];
extern void *iosMallocAlign(int, int, int);
extern int MakeStrHashValue(char *);
extern void AddStrHashKey(void *, SymEntry *);

static void func_00007968(ModObj *obj, int heap)
{
    ModInfo *info;
    char *strtab;
    SymEntry *base;
    SymEntry *p;
    Sym *sym;
    int *idx;
    ModInfo *mi;
    Sym *syms;
    int n; int n2;
    int i;
    int cnt;
    int k;

    info = obj->info;
    strtab = info->strtab;
    n = info->first ? info->first + 1 : 2;
    mi = info;
    cnt = mi->numSyms - mi->numUndef - n;
    if (cnt != 0) {
        base = iosMallocAlign(heap, cnt * 16, 4);
        obj->defs = base;
        p = base;
        n2 = mi->first ? mi->first + 1 : 2;
        i = mi->numSyms - n2;
        sym = &mi->syms[n2];
        while (i-- != 0) {
            if (sym->section != 0) {
                char *name = strtab + sym->name;

                if (*name != 0) {
                    p->sym8 = sym;
                    p->hash = MakeStrHashValue(name);
                    AddStrHashKey(B_00054398, p);
                    p->sym4 = 0;
                } else {
                    p->sym8 = 0;
                    p->sym4 = 0;
                }
                p++;
            }
            sym++;
        }
        obj->flags.rest = p - base;
    } else {
        obj->defs = 0;
    }
    k = mi->numUndef;
    if (k != 0) {
        p = obj->undefs = iosMallocAlign(heap, k * 16, 4);
        idx = mi->undef;
        syms = mi->syms;
        while (k-- != 0) {
            Sym *s = &syms[*idx++];

            p->hash = MakeStrHashValue(strtab + s->name);
            p->unkC = 0;
            p->sym8 = 0;
            p->sym4 = s;
            p++;
            s->defined = 1;
        }
    } else {
        obj->undefs = 0;
    }
    obj->flags.a = 1;
}
#endif
