typedef struct {
    int a;
    char pad4[0x4];
    int slot;
    int active;
    float value;
    char pad14[0x4];
    float time;
    char pad1C[0x70 - 0x1C];
    float b;
    float c;
} WeakPointEffect;

typedef struct {
    int kind;
    int slot;
    char pad8[0x8];
    char param[0x10];
} WeakHit;

extern int D_0017ABB0;
extern WeakPointEffect B_0018A9B0[8];
extern char gcGlobalVar[];
extern char rootPtn[];
extern char RO_0017D2C8[];
extern void func_0004CE30(WeakPointEffect *e, void *param);
extern void func_0004E960(void *e);
extern int gcCreateScriptObj(void (*)(void *), void *, void *, int, int, int, char *);

void boot_weakpoint_effect(WeakHit *hit, float a, float b, float c)
{
    WeakPointEffect *e = &B_0018A9B0[hit->slot];

    if (D_0017ABB0 == 0)
        return;
    if (e->active == 0) {
        if (a == 0.0f)
            return;
        e->a = hit->kind;
        e->active = 1;
        e->slot = hit->slot;
        func_0004CE30(e, hit->param);
        gcCreateScriptObj(func_0004E960, e, rootPtn, 0x1000, 0, 8, RO_0017D2C8);
        e->time = *(float *)(gcGlobalVar + 0x178);
        e->value = a;
        e->b = b;
        e->c = c;
    } else {
        e->value = a;
        e->time = *(float *)(gcGlobalVar + 0x178);
    }
}
