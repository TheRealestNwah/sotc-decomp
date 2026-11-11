typedef struct { int z; int pad; float val; int state; } Bar;
extern Bar B_0019CCD0[];
extern int D_0017AFEC;
extern float getDemoBarFade(void);
extern float getFadeValue(void);

static void func_000BC988(int sel)
{
    int i;

    if ((getDemoBarFade() == 1.0f && getFadeValue() == 0.0f) || D_0017AFEC != 0) {
        for (i = 0; i < 4; i++) {
            if (sel == i) {
                if (B_0019CCD0[i].state != 1) {
                    B_0019CCD0[i].state = 1;
                    B_0019CCD0[i].val = 1.0f;
                }
            } else if ((unsigned)(B_0019CCD0[i].state - 1) >= 2U) {
                B_0019CCD0[i].state = 2;
                B_0019CCD0[i].val = 0.05f;
            }
            if (B_0019CCD0[i].state != 0)
                B_0019CCD0[i].z = 0;
        }
    }
}
