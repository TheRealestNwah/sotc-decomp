#ifdef NONMATCHING
/* 83 diffs, 5 words long (137 vs 132). Draft from the asm; callee prototypes are guesses. State machine on w[0] (0 idle, 1 active, 2 releasing) with timers w[1], w[2]; when ctx+0x1838 == 1 it instead initialises two interp-ratio sub-objects (w+3 and w+0x14: zeros, -1.0f, 1.4835299f, -1.4835299f, flags 1) and calls func_000E1620 on each. Differences: gcc duplicates the epilogue instead of sharing it (original returns jump into one shared epilogue between the init block and the state code), and orders the init stores floats-first where the original stores r[0..2] zeros first. Not yet permuted. */
extern void GAMEUTIL_constructor_interp_ratio_cntrl(void *);
extern void GAMEUTIL_set_act_max_zero_clip_flag_interp_ratio_cntrl(void *, int);
extern void func_000E1620(void *);

static inline void initRatio(int *r)
{
    float *f = (float *)r;

    r[0] = 0;
    r[1] = 0;
    r[2] = 0;
    f[3] = -1.0f;
    r[4] = 1;
    f[5] = 1.4835299f;
    f[6] = -1.4835299f;
    r[7] = 1;
    r[8] = 0;
}

void CAM_doit_view_cut_avoid_cntrl(int *w, char *ctx, char **pp, float dt)
{
    int flag = *(int *)(ctx + 0x1838);
    char *c = ctx + 0x520;
    char *p = *pp;
    float *wf = (float *)w;
    int st;

    if (flag == 1) {
        int *s0 = w + 3;
        int *s1 = w + 0x14;

        w[0] = 0;
        w[2] = 0;
        w[1] = 0;
        initRatio(s0);
        GAMEUTIL_constructor_interp_ratio_cntrl(w + 0xC);
        GAMEUTIL_set_act_max_zero_clip_flag_interp_ratio_cntrl(w + 0xC, 1);
        s0[0] = 0;
        func_000E1620(s0);
        initRatio(s1);
        GAMEUTIL_constructor_interp_ratio_cntrl(w + 0x1D);
        GAMEUTIL_set_act_max_zero_clip_flag_interp_ratio_cntrl(w + 0x1D, 1);
        s1[0] = 1;
        func_000E1620(s1);
    } else {
        st = w[0];
        if (st == 1) {
            if (*(int *)(p + 0x6C) == 0x65) {
                float t = wf[1] + dt;

                wf[1] = t;
                if ((*(int *)(c + 0x44) == 0) == st)
                    goto check;
                if (!(0.25f <= t))
                    goto check;
            }
            st = 2;
            w[0] = 2;
        check:
            if (st == 2)
                w[2] = 0;
        } else {
            if (*(int *)(p + 0x6C) == 0x65 && *(int *)(c + 0x44) != 0) {
                w[0] = 1;
                wf[1] = 0.0f;
                wf[2] = 0.0f;
            } else if (st == 2) {
                float t = wf[2] + dt;

                wf[2] = t;
                if (*(float *)(p + 0x78) <= t && *(float *)(p + 0x94) <= t) {
                    w[0] = 0;
                    wf[1] = 0.0f;
                    wf[2] = 0.0f;
                }
            }
        }
    }
}
#endif
