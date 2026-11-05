typedef struct { float timer; float alpha; float speed; int state; } DispSw;
typedef struct { char pad[0x320]; int pad1; int pad2; } GcGlobal;

extern GcGlobal gcGlobalVar;
extern char padManagerData[];
extern int __gameMode;
extern DispSw B_0019CCD0[];
static void func_000BC988(int);

static void func_000BCA80(float dt)
{
    int count = 0;
    int i;
    DispSw *p;

    if (((*(unsigned int *)(padManagerData + 8) & (1 << gcGlobalVar.pad1))
         || (*(unsigned int *)(padManagerData + 8) & (1 << gcGlobalVar.pad2)))
        && !(__gameMode & 1)) {
        func_000BC988(4);
    }
    for (i = 3, p = B_0019CCD0; i >= 0; i--, p++) {
        switch (p->state) {
        case 0:
            p->timer += dt;
            if (p->timer >= 5.0f)
                count++;
            break;
        case 1:
        case 2:
            p->alpha += p->speed * dt * 30.0f;
            if (p->alpha >= 1.0f) {
                p->alpha = 1.0f;
                goto reset;
            }
            break;
        case 3:
            p->alpha += p->speed * dt * 30.0f;
            if (p->alpha <= 0.0f) {
                p->alpha = 0.0f;
            reset:
                p->state = 0;
                p->speed = 0.0f;
                p->timer = 0.0f;
            }
            break;
        }
    }
    if (count == 4) {
        for (i = 3, p = B_0019CCD0; i >= 0; i--, p++) {
            p->state = 3;
            p->speed = -0.05f;
        }
    }
}
