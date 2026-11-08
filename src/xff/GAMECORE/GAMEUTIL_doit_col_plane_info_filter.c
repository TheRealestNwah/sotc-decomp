typedef int s128 __attribute__((mode(TI)));
extern s128 YUnitVector, ZeroPoint;
extern char *GetCharacterClass(void *);
extern void GAMEUTIL_set_parameter_col_plane_info_filter(char *, float, float);

#define I(p, o) (*(int *)((p) + (o)))
#define U(p, o) (*(unsigned int *)((p) + (o)))
#define F(p, o) (*(float *)((p) + (o)))
#define P(p, o) (*(char **)((p) + (o)))

#ifdef NONMATCHING
/* Parked: 12 words differ (copy-block lq/ld scheduling). */
void GAMEUTIL_doit_col_plane_info_filter(char *f, char *in, float add)
{
    char *target;
    float d;
    int type;

    I(f, 0x60) = 0;
    I(f, 0x64) = 0;
    type = I(in, 4);
    if (type == 1) {
        target = 0;
        if (P(in, 0) != 0) {
            target = P(GetCharacterClass(P(in, 0)), 0x578);
            if (target != 0 && ((U(target, 0x6C) >> 8) & 1) == type)
                P(f, 0x68) = target;
        }
        if (I(in, 8) != 0) {
            if (I(f, 8) != 0 && !(F(f, 0x70) <= 0.0f)) {
                __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                                     "lqc2 vf6, 0x0(%2)\n"
                                     "vsub.xyzw vf7, vf5, vf6\n"
                                     "vmul.xyz vf7, vf7, vf7\n"
                                     "vaddy.x vf7, vf7, vf7y\n"
                                     "vaddz.x vf7, vf7, vf7z\n"
                                     "qmfc2.ni $2, vf7\n"
                                     "mtc1 $2, %0\n"
                                     : "=f"(d) : "r"(f + 0x30), "r"(in + 0x30) : "$2");
                F(f, 0x64) = d;
                if (!(F(f, 0x70) * F(f, 0x70) <= d)) {
                    if (P(f, 0x68) == 0 || P(f, 0x68) == target)
                        goto keep;
                }
            }
            *(long *)(f + 0x10) = *(long *)(in + 0x10);
            *(s128 *)(f + 0x20) = *(s128 *)(in + 0x20);
            *(s128 *)(f + 0x30) = *(s128 *)(in + 0x30);
            *(s128 *)(f + 0x40) = *(s128 *)(in + 0x40);
            I(f, 0x60) = 1;
            I(f, 0x68) = 0;
        keep:
            I(f, 0x6C) = 0;
            I(f, 8) = 1;
            I(f, 0x50) = I(in, 0x50);
        } else {
            F(f, 0x6C) += add;
            if (F(f, 0x74) <= F(f, 0x6C))
                I(f, 8) = 0;
            I(f, 0x50) = 0;
        }
        return;
    }
    {
        float p0 = F(f, 0x70), p1 = F(f, 0x74);
    I(f, 0) = 0;
    I(f, 4) = 0;
    I(f, 8) = 0;
    *(long *)(f + 0x10) = 0;
    *(s128 *)(f + 0x20) = YUnitVector;
    *(s128 *)(f + 0x30) = ZeroPoint;
    *(s128 *)(f + 0x40) = ZeroPoint;
    I(f, 0x50) = 0;
    I(f, 0x60) = 0;
    I(f, 0x64) = 0;
    I(f, 0x68) = 0;
    I(f, 0x6C) = 0;
        GAMEUTIL_set_parameter_col_plane_info_filter(f, p0, p1);
    }
}
#else
void GAMEUTIL_doit_col_plane_info_filter(char *f, char *in, float add);
#endif
