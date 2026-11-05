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
    for (i = 0; i < 4; i++) {
        switch (B_0019CCD0[i].state) {
        case 0:
            B_0019CCD0[i].timer += dt;
            if (B_0019CCD0[i].timer >= 5.0f)
                count++;
            break;
        case 1:
        case 2:
            B_0019CCD0[i].alpha += B_0019CCD0[i].speed * dt * 30.0f;
            if (B_0019CCD0[i].alpha >= 1.0f) {
                B_0019CCD0[i].alpha = 1.0f;
                goto reset;
            }
            break;
        case 3:
            B_0019CCD0[i].alpha += B_0019CCD0[i].speed * dt * 30.0f;
            if (B_0019CCD0[i].alpha <= 0.0f) {
                B_0019CCD0[i].alpha = 0.0f;
            reset:
                B_0019CCD0[i].state = 0;
                B_0019CCD0[i].speed = 0.0f;
                B_0019CCD0[i].timer = 0.0f;
            }
            break;
        }
    }
    if (count == 4) {
        for (i = 0; i < 4; i++) {
            B_0019CCD0[i].state = 3;
            B_0019CCD0[i].speed = -0.05f;
        }
    }
}
