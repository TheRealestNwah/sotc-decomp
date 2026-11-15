/* Parked: 106 diffs, same size (150 words; the Original continues into the split tail func_00049FC0). Animation step advance: with o+0x8C clear it advances the fractional cursor (o+0x9C) and clamps both cursors to the key count (o+0x84); otherwise it walks the key list, building a 4x4 basis from each key's quaternion (30-instruction VU0 run: cross products, vmove shuffles, ACC multiply-add) until the y of the transformed delta goes negative, writing -y to *p. Registers pinned: points base s3, quaternion pointer s2. Remaining: float temp numbering in the cursor-advance block (f2/f3/f4 vs f4/f1/f2), loop head layout, and a few delay-slot choices. */
#ifdef NONMATCHING
typedef int s128 __attribute__((mode(TI)));

typedef union {
    struct {
        float x, y, z, w;
    };
    s128 q;
} Vec;

extern char XUnitVector[];
extern char YUnitVector[];
extern void GetDifferencialQuaternionWithNoRegularize(void *, void *, void *, void *);

int func_00049DA0(char *o, float *p, int n)
{
    struct {
        Vec v;
        s128 quat;
    } L __attribute__((aligned(16)));
    register char *pts __asm__("$19");
    register s128 *qp __asm__("$18") = &L.quat;
    float step;
    float f;
    float lim;

    pts = *(char **)(o + 0x70);
    GetDifferencialQuaternionWithNoRegularize(qp, YUnitVector, o + 0xC0, XUnitVector);
    if (*(int *)(o + 0x8C) == 0) {
        n = 1;
        f = *(float *)(o + 0x9C);
        step = *(float *)(o + 0x344) / *(float *)(o + 0x7C);
        lim = f - (float)(int)f;
        f += step;
        *(float *)(o + 0x9C) = f;
        if (lim == 0.0f)
            n = 0;
        n = n + (int)f;
        if (*(int *)(o + 0x84) < n)
            n = *(int *)(o + 0x84);
        lim = (float)*(int *)(o + 0x84);
        *(float *)(o + 0x94) = *(float *)(o + 0x94) + step;
        if (lim < f)
            *(float *)(o + 0x9C) = lim;
        if (lim < *(float *)(o + 0x94))
            *(float *)(o + 0x94) = lim;
        return n;
    } else {
        *(int *)p = 0;
        while (n < *(int *)(o + 0x84)) {
            __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                                 "lqc2 vf6, 0x0(%1)\n"
                                 "vsub.xyz vf5, vf5, vf6\n"
                                 "sqc2 vf5, 0x0(%2)\n"
                                 :
                                 : "r"(pts + (n << 4)), "r"(o + 0xB0), "r"(&L.v)
                                 : "memory");
            L.v.w = 1.0f;
            __asm__ __volatile__("lqc2 vf8, 0x0(%0)\n"
                                 "vaddw.xyz vf12, vf0, vf0w\n"
                                 "lqc2 vf11, 0x0(%1)\n"
                                 "vmr32.w vf14, vf0\n"
                                 "vmr32.w vf15, vf0\n"
                                 "vmr32.w vf16, vf0\n"
                                 "vopmula.xyz ACC, vf11, vf12\n"
                                 "vmadd.xyz vf11, vf0, vf0\n"
                                 "vmadd.xyz vf10, vf11, vf12\n"
                                 "vmul.xyz vf13, vf11, vf10\n"
                                 "vopmula.xyz ACC, vf11, vf10\n"
                                 "vmaddw.xyz vf15, vf10, vf11w\n"
                                 "vmsubw.xyz vf16, vf10, vf11w\n"
                                 "vopmula.xyz ACC, vf13, vf12\n"
                                 "vmadd.xyz vf17, vf13, vf12\n"
                                 "vopmula.xyz ACC, vf15, vf12\n"
                                 "vmadd.xyz vf15, vf0, vf0\n"
                                 "vsub.xyz vf14, vf12, vf17\n"
                                 "vmove.yz vf17, vf14\n"
                                 "vmove.y vf14, vf16\n"
                                 "vmove.y vf16, vf15\n"
                                 "vmove.y vf15, vf17\n"
                                 "vmove.z vf14, vf15\n"
                                 "vmove.z vf15, vf16\n"
                                 "vmove.z vf16, vf17\n"
                                 "vmulax.xyzw ACC, vf14, vf8x\n"
                                 "vmadday.xyzw ACC, vf15, vf8y\n"
                                 "vmaddaz.xyzw ACC, vf16, vf8z\n"
                                 "vmaddw.xyzw vf10, vf0, vf8w\n"
                                 "sqc2 vf10, 0x0(%2)\n"
                                 :
                                 : "r"(&L.v), "r"(qp), "r"(&L.v)
                                 : "memory");
            step = L.v.y / *(float *)(o + 0x7C);
            *(float *)(o + 0x94) = (float)*(int *)(o + 0x90) + step;
            *(float *)(o + 0x9C) = (float)n + step;
            if (L.v.y < 0.0f) {
                *p = -L.v.y;
                return n;
            }
            if (*(int *)(o + 0x88) != 0)
                *(int *)(o + 0x90) = *(int *)(o + 0x90) + 1;
            if (*(int *)(o + 0x90) == *(int *)(o + 0x84))
                *(int *)(o + 0x90) = *(int *)(o + 0x84) - 1;
            n++;
        }
        *(int *)(o + 0x8C) = 0;
        return n;
    }
}
#endif
