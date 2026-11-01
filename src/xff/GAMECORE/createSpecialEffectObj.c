typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;
typedef union { void *p; int i; } UPtr;

typedef struct EffDef {
    char pad0[0xC];
    void (*init)(char *);
    char pad10[4];
    int (*size)(struct EffDef *);
} EffDef;

extern char *_isysCreateObj(void *, int, int, int, int, int);
extern void *iosMallocAlign(int, int, int);

char *createSpecialEffectObj(void *grp, EffDef *def, Vec4 **pp)
{
    int sz = 0;
    char *o;
    void (*init)(char *);

    if (def->size != 0)
        sz = def->size(def);
    o = _isysCreateObj(grp, 0x22, 0x40, sz + 0x33, 0, 0x10);
    if (o != 0) {
        init = def->init;
        ((UPtr *)(o + 0x1C))->p = def;
        if (sz == 0)
            *(void **)(o + 0x30) = 0;
        else
            *(void **)(o + 0x30) = iosMallocAlign(*(int *)o, sz, 0x10);
        if (pp[0] != 0) {
            ((Vec4 *)(o + 0x20))->f[0] = pp[0]->f[0] + pp[1]->f[0];
            ((Vec4 *)(o + 0x20))->f[1] = pp[0]->f[1] + pp[1]->f[1];
            ((Vec4 *)(o + 0x20))->f[2] = pp[0]->f[2] + pp[1]->f[2];
            ((Vec4 *)(o + 0x20))->f[3] = 1.0f;
        } else {
            ((Vec4 *)(o + 0x20))->q = pp[1]->q;
        }
        init(o);
    }
    return o;
}
