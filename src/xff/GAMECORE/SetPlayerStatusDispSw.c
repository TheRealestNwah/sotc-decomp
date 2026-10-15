typedef struct { float a; int b; float c; int state; } DispSw;
extern DispSw B_0019CCD0[];
static void func_000BC988(int);

void SetPlayerStatusDispSw(int on)
{
    int i;
    if (on != 0) {
        func_000BC988(4);
        return;
    }
    for (i = 0; i < 4; i++) {
        if (B_0019CCD0[i].state != 3) {
            B_0019CCD0[i].state = 3;
            B_0019CCD0[i].c = -0.05f;
            B_0019CCD0[i].a = 5.0f;
        }
    }
}
