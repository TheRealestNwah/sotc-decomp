typedef int s128 __attribute__((mode(TI)));
extern s128 ZeroPoint;
extern s128 ZUnitVector;
extern int is_reset_or_lws_movie_or_cutout_game_camera(int);
extern int func_000D76A0(char *, char *, int, int);
extern int func_000D77D8(char *, char *, int, float);
extern void func_000D78D8(char *, char *, float);

#ifdef NONMATCHING /* 35 diffs: control flow and calls match; the zero-point/Z-unit vector copy block is scheduled differently (lui reg, store order) and the tail-call region carries an extra nop */
static void func_000D7260(char *s, char *c, int a2, int a3, float dt)
{
    int r;
    int st;
    float t;
    char *q;

    if (is_reset_or_lws_movie_or_cutout_game_camera(a2) == 1) {
        *(int *)s = 0;
        *(float *)(s + 8) = 1.0f;
        *(float *)(s + 4) = 0.0f;
        *(s128 *)(s + 0x10) = ZeroPoint;
        *(int *)(s + 0x30) = 0;
        *(s128 *)(s + 0x20) = ZUnitVector;
        return;
    }
    if (*(unsigned int *)s < 2U) {
        r = func_000D76A0(s, c, a2, a3);
        if (r != 0) {
            q = c + 0x520;
            t = *(float *)(s + 4) + dt;
            *(float *)(s + 4) = t;
            st = 0;
            if (r != 1 || *(int *)(q + 0xB0) == 2 || *(float *)(c + 0x14) <= t)
                st = 1;
            if (st == 1) {
                *(int *)s = 2;
            {
                float d;
                __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                                     "lqc2 vf6, 0x0(%2)\n"
                                     "vsub.xyzw vf7, vf5, vf6\n"
                                     "vmul.xyz vf7, vf7, vf7\n"
                                     "vmulax.w ACC, vf0, vf7x\n"
                                     "vmadday.w ACC, vf0, vf7y\n"
                                     "vmaddz.w vf7, vf0, vf7z\n"
                                     ".word 0x4BA703BD\n"
                                     "vwaitq\n"
                                     "cfc2.ni $2, $vi22\n"
                                     "mtc1 $2, %0\n"
                                     : "=f"(d) : "r"(c + 0x60), "r"(q) : "$2");
                *(float *)(s + 8) = d;
            }
                func_000D78D8(s, c, t);
                *(float *)(s + 4) = 0.0f;
                return;
            }
            *(int *)s = 1;
            return;
        }
        *(float *)(s + 4) = 0.0f;
        return;
    }
    if (func_000D76A0(s, c, a2, a3) != 0) {
        func_000D78D8(s, c, dt);
        return;
    }
    if (func_000D77D8(s, c, a2, dt) == 1)
        *(int *)s = 0;
}
#endif
