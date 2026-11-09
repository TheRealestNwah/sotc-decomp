typedef struct { int name; int value; int size; char info; char other; unsigned short shndx; } Sym;
typedef struct { unsigned int offset; unsigned int info; } Rel;
typedef struct { int type; int count; int pad8; Rel *rels; char pad10[0xC]; } RelSect;
typedef struct {
    char pad0[0x1C];
    int relocatable;
    char pad20[8];
    Sym *syms;
    char pad2C[0xC];
    int nsects;
    RelSect *sects;
} ModInfo;
typedef struct { RelSect *sect; int idx; } Undef;
typedef struct { int count; Undef *list; } UndefList;

extern void *iosMallocAlign(int, int, int);

#ifdef NONMATCHING
/* Parked: 5 words differ (order of the list store and the nsects reload) */
static void func_00007F80(UndefList *out, int heap, ModInfo *info)
{
    out->count = 0;
    out->list = 0;
    if (info->relocatable != 0) {
        Sym *syms = info->syms;
        int n = info->nsects;
        RelSect *s = info->sects;
        Undef *u;

        while (n--) {
            if (s->type == 4 || s->type == 9) {
                int j = s->count;
                Rel *r = s->rels;
                while (j--) {
                    if (syms[r->info >> 8].shndx == 0) {
                        out->count++;
                    }
                    r++;
                }
            }
            s++;
        }
        u = (out->list = iosMallocAlign(heap, out->count * 8, 4));
        n = info->nsects;
        {RelSect *s = info->sects;
        while (n--) {
            if (s->type == 4 || s->type == 9) {
                int idx = 0;
                int j = s->count;
                Rel *r = s->rels;
                while (j--) {
                    if (syms[r->info >> 8].shndx == 0) {
                        u->idx = idx;
                        u->sect = s;
                        u++;
                    }
                    idx++;
                    r++;
                }
            }
            s++;
        }}
    }
}
#endif
