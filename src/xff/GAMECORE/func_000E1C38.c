typedef unsigned int u_long128 __attribute__((mode(TI)));

typedef struct {
    char pad0[0x2C];
    int x2C;
    u_long128 x30;
} NoiseWork;

extern char *GetLayoutClass(void *);
extern float GAMEUTIL_get_object_move_noise(void *);

static void func_000E1C38(NoiseWork *w, char *obj)
{
    void *target = *(void **)(obj + 0x23C);
    float noise;
    float d;

    if (*(int *)(obj + 0x1838) == 1) {
        w->x2C = 1;
        w->x30 = **(u_long128 **)(GetLayoutClass(target) + 0x134);
    } else if (w->x2C == 1) {
        noise = GAMEUTIL_get_object_move_noise(target);
        __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                             "lqc2 vf6, 0x0(%2)\n"
                             "vsub.xyzw vf7, vf5, vf6\n"
                             "vmul.xyz vf7, vf7, vf7\n"
                             "vaddy.x vf7, vf7, vf7y\n"
                             "vaddz.x vf7, vf7, vf7z\n"
                             "qmfc2.ni $2, vf7\n"
                             "mtc1 $2, %0\n"
                             : "=f"(d) : "r"(*(float **)(GetLayoutClass(target) + 0x134)), "r"(&w->x30) : "$2");
        if (noise * noise <= d) {
            w->x2C = 0;
        }
    }
}
