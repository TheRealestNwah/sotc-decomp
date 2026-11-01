typedef struct {
    int a;
    int b;
} Pair;

extern void ParentLayoutObj(void *, void *);
extern void func_000677B8(void *, int);
extern void charrootdyn_getLocalOffsetFromParentGP(void *, int, int, void *);

void motrootdyn_startedgepoint(void *self, char *p)
{
    char *q;
    Pair *src;
    Pair *dst;
    if (*(int *)(p + 0xF3C) != 0 && *(int *)(p + 0xE70) != 0) {
        ParentLayoutObj(self, p + 0xE90);
        func_000677B8(p, 0);
        charrootdyn_getLocalOffsetFromParentGP(p + 0x6D0, *(int *)(p + 0x13C), *(int *)(p + 0x134), p + 0xC0);
        dst = (Pair *)(p + 0x674);
        if (*(int *)(p + 0xED0) != 0) {
            src = (Pair *)(p + 0xED4);
            *(int *)(p + 0x670) = 1;
            dst->a = src->a;
            dst->b = src->b;
        } else {
            *(int *)(p + 0x670) = 0;
        }
    } else if (*(int *)(p + 0x610) != 0) {
        ParentLayoutObj(self, p + 0x630);
        func_000677B8(p, 0);
        charrootdyn_getLocalOffsetFromParentGP(p + 0x6D0, *(int *)(p + 0x13C), *(int *)(p + 0x134), p + 0xC0);
    }
    q = *(char **)(p + 0x19C);
    *(char *)(q + 0x8E) = 0;
    *(char *)(q + 0x8D) = 0;
}
