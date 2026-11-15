/* Parked: 58 diffs, same size (119 words vs 117 expected before the frame fix). Boss camera blend: VU0 normalise of obj+0xB0 (vmul.xyz/vrsqrt/vmulq run) into an axis, GetQuaternionByAxisDirZY, two clamped 0..1 ratios, func_000C0EB0 and func_000C1440; no boss path memsets two identity quats. One local struct pins the frame (axis +0, quat +0x10, a +0x20, b +0x30). Remaining: the Original keeps f12 in f22 and a shared zero in caller-saved f1 (ours spends f22/f23 on it), frame 0x70 vs 0x80. */
#ifdef NONMATCHING
typedef int s128 __attribute__((mode(TI)));

extern int bossStatGetActiveBoss(void);
extern void GetQuaternionByAxisDirZY(void *, void *, void *);
extern void func_000C0EB0(float, float);
extern void func_000C1440(void *, void *, int, float, float, float);
extern void *memset(void *, int, unsigned int);
extern char D_0017B090[];
extern float D_0017B0BC;
extern float D_0017B0C0;
extern float D_0017B0C4;
extern float D_0017B0C8;
extern float D_0017B0D4;
extern float D_0017B128;
extern float D_0017B12C;

typedef struct {
    float x, y, z, w;
} Vec;

void func_000C1BA8(char *obj, float f12, float f13)
{
    struct {
        Vec axis;
        s128 quat;
        Vec a;
        Vec b;
    } L __attribute__((aligned(16)));
    float t;
    float r1;
    float r2;

    if (bossStatGetActiveBoss() != 0) {
        __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                             "vmul.xyz vf7, vf5, vf5\n"
                             "vmulax.w ACC, vf0, vf7x\n"
                             "vmadday.w ACC, vf0, vf7y\n"
                             "vmaddz.w vf7, vf0, vf7z\n"
                             "vrsqrt Q, vf0w, vf7w\n"
                             "vwaitq\n"
                             "vmulq.xyz vf5, vf5, Q\n"
                             "sqc2 vf5, 0x0(%1)\n"
                             :
                             : "r"(obj + 0xB0), "r"(&L.axis)
                             : "memory");
        GetQuaternionByAxisDirZY(&L.quat, &L.axis, D_0017B090);
        t = (f13 - D_0017B0BC) / (D_0017B0C0 - D_0017B0BC);
        r1 = 0.0f;
        if (!(t < 0.0f)) {
            r1 = 1.0f;
            if (!(1.0f < t))
                r1 = t;
        }
        t = (f13 - D_0017B0C4) / (D_0017B0C8 - D_0017B0C4);
        r2 = 0.0f;
        if (!(t < 0.0f)) {
            r2 = 1.0f;
            if (!(1.0f < t))
                r2 = t;
        }
        func_000C0EB0((f12 - D_0017B128) / (D_0017B12C - D_0017B128), f13);
        func_000C1440(&L.quat, obj, 1, f12 * D_0017B0D4, r1, r2);
    } else {
        memset(&L.a, 0, 0x10);
        L.a.w = 1.0f;
        memset(&L.b, 0, 0x10);
        L.b.w = 1.0f;
        func_000C1440(&L.b, &L.a, 1, 0.0f, 0.0f, 0.0f);
    }
}
#endif
