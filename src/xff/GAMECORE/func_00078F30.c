typedef int s128 __attribute__((mode(TI)));
extern int is_doing_nico_sight_on(void *);
extern void reset_double_spring_interp_cntrl(void *, float);
extern void GAMEUTIL_get_1p_left_analog_input_extend(float *, float *, int, float);
extern float GetWeaponRange(void);
extern void doit_nico_sight_on(void *, float, float, float);
extern char *GetLayoutClass(void *);
extern void sprWeaponSetMarker(void *, void *, int);
extern s128 ZeroPoint;
extern void func_00079220(void *, void *);
extern void func_00079060(float *, char *, void *);

static void func_00078F30(void *ctx, char *c)
{
    float in[2];
    int on;

    *(s128 *)(c + 0x40) = *(s128 *)(c + 0x30);
    c[0x51] = c[0x50];
    on = is_doing_nico_sight_on(c + 0x190);
    if (on == 1) {
        GAMEUTIL_get_1p_left_analog_input_extend(in, in + 1, 0, 0.3f);
        if (*(int *)(c + 0x180) == 0) {
            func_00079220(ctx, c);
            doit_nico_sight_on(c + 0x190, GetWeaponRange(), in[0], in[1]);
        }
        func_00079060((float *)(c + 0x30), c, ctx);
        c[0x50] = on;
        sprWeaponSetMarker(c + 0x30, *(void **)(GetLayoutClass(ctx) + 0x134), 1);
        *(int *)(c + 0x188) = on;
    } else {
        reset_double_spring_interp_cntrl(c + 0x470, 1.0f);
        {
            s128 z = ZeroPoint;
            c[0x50] = 0;
            *(s128 *)(c + 0x30) = z;
        }
        sprWeaponSetMarker(0, 0, 0);
    }
}
