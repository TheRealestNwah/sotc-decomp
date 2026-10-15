typedef struct Ptn Ptn;
extern Ptn rootPtn;
typedef struct { int a, b; void *arg; void *obj; } DemoInfo;
extern DemoInfo activedemoInfo;
extern void func_0000E828();
extern void *createScriptObj(void *, void *, Ptn *, int, int, int, int, int);

void activeDemoStandby(void *a)
{
    DemoInfo *d = &activedemoInfo;
    if (d->obj == 0) {
        d->arg = a;
        d->obj = createScriptObj(func_0000E828, 0, &rootPtn, 0x1000, 0, 1, 0, 0);
    }
}
