extern int B_0019CCD0[];
extern int B_0019CCDC;
extern int D_0017AFEC;
extern float getDemoBarFade(void);
extern float getFadeValue(void);

#ifdef NONMATCHING /* 31 diffs: induction-variable and flag-address (lui/addiu section-relative form) allocation */
static void func_000BC988(int sel)
{
    int *state;
    int *val;
    int off;
    int i;

    if ((getDemoBarFade() == 1.0f && getFadeValue() == 0.0f) || D_0017AFEC != 0) {
        state = &B_0019CCDC;
        i = 0;
        val = &B_0019CCDC - 4;
        off = 0;
        do {
            int cur = *state;

            if (sel == i) {
                if (cur != 1) {
                    *state = 1;
                    *(float *)val = 1.0f;
                }
            } else if ((unsigned)(cur - 1) >= 2U) {
                *state = 2;
                *(float *)val = 0.05f;
            }
            {
                int now = *state;

                state += 4;
                if (now != 0)
                    *(int *)((char *)B_0019CCD0 + off) = 0;
            }
            i++;
            val += 4;
            off += 0x10;
        } while (i < 4);
    }
}
#endif
