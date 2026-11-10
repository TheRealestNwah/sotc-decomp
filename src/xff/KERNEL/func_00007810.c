typedef struct {
    int offset;
    unsigned int info;
} Rel;

typedef struct {
    int type;
    int count;
    int pad8;
    Rel *rels;
} RelSect;

typedef struct {
    char pad0[0xD];
    unsigned char flag;
    unsigned short shndx;
} Sym;

typedef struct {
    char pad0[0x1C];
    int nlist;
    int *list;
    int pad24;
    Sym *syms;
} ModInfo;

typedef struct {
    RelSect *sect;
    int idx;
} Undef;

typedef struct {
    char pad0[0x1C];
    ModInfo *info;
    char pad20[0xC];
    int flags;
    int nundef;
    Undef *undef;
} ModObj;

extern void RelocateCode(ModInfo *);
extern void ResolveRelocation(ModInfo *, RelSect *, int);

static void func_00007810(ModObj *obj, int mode)
{
    ModInfo *info;

    if (obj->flags & 0x40000000) {
        return;
    }
    info = obj->info;
    if (mode) {
        RelocateCode(info);
        if (info->nlist != 0) {
            int n = info->nlist;
            int *p = info->list;
            Sym *syms = info->syms;
            while (n--) {
                syms[*p++].flag = 0;
            }
        }
    } else if (info->nlist != 0) {
        int j = obj->nundef;
        Undef *u = obj->undef;
        while (j--) {
            Rel *r = &u->sect->rels[u->idx];
            if (info->syms[r->info >> 8].flag) {
                ResolveRelocation(info, u->sect, u->idx);
            }
            u++;
        }
        {
            Sym *syms = info->syms;
            int n = info->nlist;
            int *p = info->list;
            while (n--) {
                syms[*p++].flag = 0;
            }
        }
    }
}
