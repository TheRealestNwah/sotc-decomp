typedef int s128 __attribute__((mode(TI)));

extern void iosGetExceptAxisVector(void *, void *, void *);
extern int GAMEUTIL_check_and_get_normalize_vector(void *, float *, void *);
extern float iosGetACosfExact(float);
extern float GAMEUTIL_get_interp_value(float, float, float);
extern float GAMEUTIL_doit_interp_ratio_cntrl(void *, float);
extern float GAMEUTIL_get_interp_ratio_interp_ratio_cntrl(void *);
extern void GAMEUTIL_get_local_directionZ(void *, void *);
extern float GAMEUTIL_get_dist_ratio(float, float, float);

typedef struct {
    float angle;   /* 0x00 */
    float len;     /* 0x04 */
    float diff;    /* 0x08 */
    float ratio;   /* 0x0C */
    int crossed;   /* 0x10 */
    int near;      /* 0x14 */
    int mode;      /* 0x18 */
    char cntrl[0x20]; /* 0x1C */
    float f3C;
    float f40;
    float f44;
    float f48;
    float f4C;
    float f50;
} Look;

static inline float vdot(void *a, void *b)
{
    register float r asm("$2");
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vaddw.x vf7, vf0, vf0w\n"
                         "vmul.xyz vf6, vf5, vf6\n"
                         "vaddax.x ACC, vf0, vf6x\n"
                         "vmadday.x ACC, vf7, vf6y\n"
                         "vmaddz.x vf6, vf7, vf6z\n"
                         "qmfc2.ni %0, vf6\n"
                         : "=r"(r) : "r"(a), "r"(b) : "memory");
    return r;
}

static inline void vcross(void *out, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vopmula.xyz ACC, vf5, vf6\n"
                         "vopmsub.xyz vf7, vf6, vf5\n"
                         "vsub.w vf7, vf7, vf7\n"
                         "sqc2 vf7, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline void vscale(void *out, void *a, float s)
{
    __asm__ __volatile__("mfc1 $2, %2
"
                         "lqc2 vf5, 0x0(%1)
"
                         "qmtc2.ni $2, vf6
"
                         "vmulx.xyz vf5, vf5, vf6x
"
                         "sqc2 vf5, 0x0(%0)
"
                         : : "r"(out), "r"(a), "f"(s) : "$2", "memory");
}

static inline void vsub(void *out, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

float GAMEUTIL_doit_look_at_vs_offset_vec(Look *s, void *unused, void *dir, void *mtx, void *target, void *axis,
                                          float unused_f, float speed)
{
    s128 v[4];
    float len;
    float res;
    float diff;
    float prev;
    int ok;

    len = 0.0f;
    diff = len;
    res = s->angle;
    iosGetExceptAxisVector(&v[0], dir, axis);
    iosGetExceptAxisVector(&v[1], target, axis);
    ok = GAMEUTIL_check_and_get_normalize_vector(&v[0], &len, &v[0]);
    if (ok == 1 && GAMEUTIL_check_and_get_normalize_vector(&v[1], 0, &v[1]) == ok) {
        prev = s->angle;
        diff = iosGetACosfExact(vdot(&v[0], &v[1]));
        if (diff <= s->f40) {
            res = s->f48;
        } else if (s->f44 <= diff) {
            res = s->f4C;
        } else {
            res = GAMEUTIL_get_interp_value(s->f4C, s->f48, (diff - s->f40) / (s->f44 - s->f40));
        }
        if (diff <= s->f50 || prev == 0.0f) {
            float lim = s->f3C;
            vcross(&v[2], &v[0], &v[1]);
            if (vdot(&v[2], axis) < 0.0f) {
                res = -res;
            }
            if (prev * res < 0.0f && diff < lim) {
                res = s->f48;
                if (prev < 0.0f) {
                    res = -res;
                }
            }
            s->near = 1;
        } else {
            if (prev < 0.0f) {
                res = -res;
            }
            s->near = 0;
        }
    }
    if (s->mode == 1) {
        GAMEUTIL_doit_interp_ratio_cntrl(s->cntrl, speed);
    } else {
        GAMEUTIL_doit_interp_ratio_cntrl(s->cntrl, -speed);
    }
    if (0.0f < GAMEUTIL_get_interp_ratio_interp_ratio_cntrl(s->cntrl) && mtx != 0) {
        GAMEUTIL_get_local_directionZ(&v[2], mtx);
        vscale(&v[3], axis, vdot(&v[2], axis));
        vsub(&v[2], &v[2], &v[3]);
        if (GAMEUTIL_check_and_get_normalize_vector(&v[2], 0, &v[2]) == 1) {
            float a;
            if (vdot(&v[2], &v[0]) < 0.0f) {
                a = -vdot(&v[2], &v[0]);
            } else {
                a = vdot(&v[2], &v[0]);
            }
            a = iosGetACosfExact(a);
            s->ratio = (1.5707963f - a) / 1.5707963f;
            s->ratio = GAMEUTIL_get_dist_ratio(s->ratio, 0.099999996f, 0.79999995231628418f);
            s->ratio = GAMEUTIL_get_interp_value(s->ratio, 1.0f, GAMEUTIL_get_interp_ratio_interp_ratio_cntrl(s->cntrl));
        }
    } else {
        s->ratio = 1.0f;
    }
    {
        int c = 0;
        if (s->angle != res) {
            c = 1;
            if (!(s->angle * res <= 0.0f)) {
                c = 0;
            }
        }
        if (c) {
            s->crossed = 1;
        } else {
            s->crossed = 0;
        }
    }
    s->diff = diff;
    s->angle = res;
    s->len = len;
    return res;
}
