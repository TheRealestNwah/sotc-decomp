/* 4 diffs: the Original moves the x square from $f12 to $f21 in the bc1f delay slot and scales $f21. */
#ifdef NONMATCHING
typedef int s128 __attribute__((mode(TI)));
extern float D_0012FDE0;
extern int D_0012FDE4;
extern unsigned char padManagerData[];
extern float YUnitVector[];
extern char *iosgluGetCameraContext(void);
extern void iosRotMatrixAxis(void *, void *, int, float);

static inline float sqrtF(float x)
{
    float r;
    __asm__ __volatile__("sqrt.s %0, %1" : "=f"(r) : "f"(x));
    return r;
}

#define deadzone(v, an, d) ((v < 0.0f ? -1.0f : 1.0f) * (((v < 0.0f ? -v : v) - d) * (an / (an - d))))

int DEBUG_update_direction(s128 *out, s128 *in, int pad2)
{
    float x;
    float y;
    float mag;
    float inv;
    float tx;
    float ty;
    float atx;
    float aty;
    float dy;
    float scale;
    unsigned char *p;
    char *cam;
    s128 axis0[1];
    s128 axis1[1];
    float mat[16] __attribute__((aligned(16)));
    float rot1[16] __attribute__((aligned(16)));
    float neg;
    s128 *axis0p;
    float dx;
    float rot2[16] __attribute__((aligned(16)));

    *out = *in;
    if (D_0012FDE4 != 0) {
    p = padManagerData;
    axis0p = axis0;
    if ((*(int *)p & 3) || (*(int *)(p + 0xF98) & 3)) {
        return 0;
    }
    if (pad2 != 0) {
        neg = p[0x57] / 127.5f - 1.0f;
        x = -neg;
        y = p[0x56] / 127.5f - 1.0f;
    } else {
        x = -(p[0xFEF] / 127.5f - 1.0f);
        y = p[0xFEE] / 127.5f - 1.0f;
    }
    if (y * y + x * x < 0.15999997f) {
        x = 0.0f;
        y = x;
    } else {
        mag = sqrtF(y * y + x * x);
        inv = 1.0f / mag;
        tx = x * inv;
        ty = y * inv;
        if (1.0f < mag) {
            y = ty;
            x = tx;
        } else {
            aty = ty < 0.0f ? -ty : ty;
            atx = tx < 0.0f ? -tx : tx;
            dy = aty * 0.4f;
            dx = atx * 0.4f;
            y = (y < 0.0f ? -y : y) < dy ? 0.0f : deadzone(y, aty, dy);
            x = (x < 0.0f ? -x : x) < dx ? 0.0f : deadzone(x, atx, dx);
        }
    }
    {float ys = y < 0.0f ? y * -y : y * y;
    float xs = x < 0.0f ? x * -x : x * x;
    if (ys == 0.0f && xs == 0.0f) {
        return 0;
    }
    scale = D_0012FDE0 * 6.5f;
    x = xs * scale;
    y = ys * scale;}
    cam = iosgluGetCameraContext() + 0x150;
    __asm__ __volatile__("lqc2 vf05, 0(%1)
"
                         "lqc2 vf06, 0(%2)
"
                         "vopmula.xyz ACC, vf05, vf06
"
                         "vopmsub.xyz vf07, vf06, vf05
"
                         "vsub.w vf07, vf07, vf07
"
                         "sqc2 vf07, 0(%0)
"
                         : : "r"(axis0), "r"(cam), "r"(YUnitVector) : "memory");
    cam = iosgluGetCameraContext() + 0x150;
    __asm__ __volatile__("lqc2 vf05, 0(%1)
"
                         "lqc2 vf06, 0(%2)
"
                         "vopmula.xyz ACC, vf05, vf06
"
                         "vopmsub.xyz vf07, vf06, vf05
"
                         "vsub.w vf07, vf07, vf07
"
                         "sqc2 vf07, 0(%0)
"
                         : : "r"(axis1), "r"(cam), "r"(axis0) : "memory");
    iosRotMatrixAxis(rot1, axis1, 0, y);
    iosRotMatrixAxis(rot2, axis0p, 0, x);
    __asm__ __volatile__("lqc2 vf14, 0x0(%1)
"
                         "lqc2 vf15, 0x10(%1)
"
                         "lqc2 vf16, 0x20(%1)
"
                         "lqc2 vf17, 0x30(%1)
"
                         "lqc2 vf24, 0x0(%2)
"
                         "lqc2 vf25, 0x10(%2)
"
                         "lqc2 vf26, 0x20(%2)
"
                         "lqc2 vf27, 0x30(%2)
"
                         "vmulax.xyzw ACC, vf14, vf24x
"
                         "vmadday.xyzw ACC, vf15, vf24y
"
                         "vmaddaz.xyzw ACC, vf16, vf24z
"
                         "vmaddw.xyzw vf24, vf17, vf24w
"
                         "vmulax.xyzw ACC, vf14, vf25x
"
                         "vmadday.xyzw ACC, vf15, vf25y
"
                         "vmaddaz.xyzw ACC, vf16, vf25z
"
                         "vmaddw.xyzw vf25, vf17, vf25w
"
                         "vmulax.xyzw ACC, vf14, vf26x
"
                         "vmadday.xyzw ACC, vf15, vf26y
"
                         "vmaddaz.xyzw ACC, vf16, vf26z
"
                         "vmaddw.xyzw vf26, vf17, vf26w
"
                         "vmulax.xyzw ACC, vf14, vf27x
"
                         "vmadday.xyzw ACC, vf15, vf27y
"
                         "vmaddaz.xyzw ACC, vf16, vf27z
"
                         "vmaddw.xyzw vf27, vf17, vf27w
"
                         "sqc2 vf24, 0x0(%0)
"
                         "sqc2 vf25, 0x10(%0)
"
                         "sqc2 vf26, 0x20(%0)
"
                         "sqc2 vf27, 0x30(%0)
"
                         : : "r"(mat), "r"(rot2), "r"(rot1) : "memory");
    __asm__ __volatile__("lqc2 vf8, 0x0(%2)
"
                         "lqc2 vf14, 0x0(%1)
"
                         "lqc2 vf15, 0x10(%1)
"
                         "lqc2 vf16, 0x20(%1)
"
                         "lqc2 vf17, 0x30(%1)
"
                         "vmulax.xyzw ACC, vf14, vf8x
"
                         "vmadday.xyzw ACC, vf15, vf8y
"
                         "vmaddaz.xyzw ACC, vf16, vf8z
"
                         "vmaddw.xyzw vf10, vf17, vf8w
"
                         "sqc2 vf10, 0x0(%0)
"
                         : : "r"(out), "r"(mat), "r"(in) : "memory");
    return 1;
    }
    return 0;
}
#endif
