/* doit_expression: interp-value update for an expression controller (~8 diffs: _setRootXYZHPB arg
 * setup order -- original moves f12-f17 first, a3/t0 last. The volatile stores keep the zero-clear
 * order; the original probably used a struct here.) */
extern char *GetCharacterClass(int);
extern int GAMEUTIL_is_status_change_status_manager(void *);
extern void GAMEUTIL_reset_interp_ratio_cntrl(void *);
extern void GAMEUTIL_set_param_interp_ratio_cntrl(void *, float, float);
extern void GAMEUTIL_doit_interp_ratio_cntrl(void *, float);
extern void GAMEUTIL_doit_interp_value_cntrl(void *, void *, float);
extern float GAMEUTIL_get_interp_value_interp_value_cntrl(void *);
extern void _setRootXYZHPB(int, int, int, int, int, float, float, float, float, float, float);
extern void _setNodeHPB(int, int, int, int, int, float, float, float);

#ifdef NONMATCHING
void doit_expression(char *o, float a, float b)
{
    int i;
    char *cls = GetCharacterClass(*(int *)o);
    int s4 = *(int *)(cls + 0x358);
    int s8 = *(int *)(cls + 0x2E8);
    char *ic = o + 0x14;
    char *p44;
    char *p;
    char *q;
    char *r;
    char *t;
    char *u;
    char *w;
    char *m;
    int sp10;
    float f0, f1, f2, f3, f4;

    if (GAMEUTIL_is_status_change_status_manager(o + 4) == 1)
        GAMEUTIL_reset_interp_ratio_cntrl(ic);
    p44 = o + 0x44;
    GAMEUTIL_set_param_interp_ratio_cntrl(ic, 0.0f, a);
    p = o + 0x34;
    GAMEUTIL_doit_interp_ratio_cntrl(ic, b);
    t = o + 0x50;
    u = o + 0x5C;
    GAMEUTIL_doit_interp_value_cntrl(p44, ic, *(float *)(p + 4));
    q = o + 0x78;
    r = o + 0x84;
    GAMEUTIL_doit_interp_value_cntrl(t, ic, *(float *)(p + 8));
    sp10 = (int)(cls + 0x470);
    i = 0;
    GAMEUTIL_doit_interp_value_cntrl(u, ic, *(float *)(p + 0xC));
    w = o + 0x90;
    GAMEUTIL_doit_interp_value_cntrl(q, ic, *(float *)(p + 0x38));
    GAMEUTIL_doit_interp_value_cntrl(r, ic, *(float *)(p + 0x3C));
    GAMEUTIL_doit_interp_value_cntrl(w, ic, *(float *)(p + 0x40));
    f0 = GAMEUTIL_get_interp_value_interp_value_cntrl(q);
    f1 = GAMEUTIL_get_interp_value_interp_value_cntrl(r);
    f2 = GAMEUTIL_get_interp_value_interp_value_cntrl(w);
    f3 = GAMEUTIL_get_interp_value_interp_value_cntrl(p44);
    f4 = GAMEUTIL_get_interp_value_interp_value_cntrl(t);
    _setRootXYZHPB(s4, s8, sp10, (int)(cls + 0x40), (int)(cls + 0x90), f0, f1, f2, f3, f4,
                   GAMEUTIL_get_interp_value_interp_value_cntrl(u));
    *(volatile float *)(p + 4) = 0.0f;
    *(volatile float *)(p + 0x40) = 0.0f;
    *(volatile float *)(p + 8) = 0.0f;
    *(volatile float *)(p + 0xC) = 0.0f;
    *(volatile int *)(p + 0x34) = 0;
    *(volatile float *)(p + 0x38) = 0.0f;
    *(volatile float *)(p + 0x3C) = 0.0f;
    if (*(volatile int *)(o + 0x9C) > 0) {
        m = o;
        do {
            float g0, g1;
            GAMEUTIL_doit_interp_value_cntrl(m + 0xB0, ic, *(float *)(m + 0xA4));
            GAMEUTIL_doit_interp_value_cntrl(m + 0xBC, ic, *(float *)(m + 0xA8));
            i++;
            GAMEUTIL_doit_interp_value_cntrl(m + 0xC8, ic, *(float *)(m + 0xAC));
            g0 = GAMEUTIL_get_interp_value_interp_value_cntrl(m + 0xB0);
            g1 = GAMEUTIL_get_interp_value_interp_value_cntrl(m + 0xBC);
            _setNodeHPB(*(int *)(*(int *)(m + 0xA0) + 8), s4, s8, sp10, *(int *)(m + 0xD4), g0, g1,
                        GAMEUTIL_get_interp_value_interp_value_cntrl(m + 0xC8));
            *(int *)(m + 0xA4) = 0;
            *(int *)(m + 0xA8) = 0;
            *(int *)(m + 0xAC) = 0;
            m += 0x38;
        } while (i < *(int *)(o + 0x9C));
    }
}
#endif
