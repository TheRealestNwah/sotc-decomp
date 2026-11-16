typedef struct {
    char pad0[0x3E0];
    char *info;
    char pad3E4[4];
    char *buf;
} WinOwner;

typedef struct {
    char pad0[8];
    void (*fn)(int, void *);
    char padC[0x2C];
} CbEntry;

typedef struct {
    char pad0[0xC];
    union { int *i; float *f; } val, min, max;
    int type;
    int arg;
    CbEntry *table;
    int index;
} NumInfo;

extern long atol(const char *);
extern double atof(const char *);
extern void iosFree(void *);
extern int B_0014E878;

static void func_000D2DD0(void *unused, WinOwner *o)
{
    char *buf = o->buf;
    NumInfo *info = (NumInfo *)o->info;
    CbEntry *t;

    if (*buf != 0) {
        switch (info->type) {
        case 0:
            *info->val.i = atol(buf);
            if (*info->val.i > *info->max.i)
                *info->val.i = *info->max.i;
            if (*info->val.i < *info->min.i)
                *info->val.i = *info->min.i;
            break;
        case 2:
            *info->val.f = atof(buf);
            if (*info->val.f > *info->max.f)
                *info->val.f = *info->max.f;
            if (*info->val.f < *info->min.f)
                *info->val.f = *info->min.f;
            break;
        }
        t = info->table;
        if (t != 0 && t[info->index].fn != 0)
            t[info->index].fn(info->arg, t);
    }
    B_0014E878 = 0;
    iosFree(info);
}
