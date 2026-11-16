/* Parked: 59 diffs, same size (90 words). Plane-segment clip against a limit: lim[0] * scale->0x14 compared with the p/q components picked by (bits & 3); when only one end is inside, lerps to the crossing with a VU0 run (qmtc2 t, vsubx.w, vmulax, vmaddw) into a stack temp and hands it to func_000B69F0 together with a table entry; bits < 0 goes to func_000B0BC8. Args are passed through in a0..a3/t0 (the callees get the original registers). Register pins match the Original's t2/t4/t5/t3 copies. Remaining: delay-slot filling of the qv - pv subtract (beql), the two-temp frame (0x30 vs 0x20), and branch order of the inner cases. */
#ifdef NONMATCHING
typedef int s128 __attribute__((mode(TI)));

extern int func_000B0BC8(int, void *, void *, void *, int);
extern int func_000B69F0(int, void *, void *, void *, int);

int func_000B1380(int a0, s128 *a1p, s128 *a2p, char *workp, float *lim, char *scale)
{
    register s128 *a1 __asm__("$12") = a1p;
    register s128 *a2 __asm__("$10") = a2p;
    register char *work __asm__("$13") = workp;
    s128 tmpA __attribute__((aligned(16)));
    s128 tmpB __attribute__((aligned(16)));
    register unsigned int bits __asm__("$11") = *(unsigned int *)((char *)lim + 4);
    float limit = lim[0] * *(float *)(scale + 0x14);
    int idx = bits & 3;
    float pv = ((float *)a1)[idx];
    float qv = ((float *)a2)[idx];
    int inP = 0;
    int inQ = 0;
    int ret = 0;
    float t;

    inP = limit <= pv ? 1 : 0;
    inQ = limit <= qv ? 1 : 0;
    if (inP != 0 || inQ != 0) {
        if ((int)bits < 0) {
            ret = func_000B0BC8(a0, a1, a2, work, (bits >> 17) & 0x3FFF);
        } else if (inP == 0) {
            t = (limit - pv) / (qv - pv) - 0.0f;
            __asm__ __volatile__("qmtc2.ni %0, vf7\n"
                                 "lqc2 vf5, 0x0(%1)\n"
                                 "lqc2 vf6, 0x0(%2)\n"
                                 "vsubx.w vf8, vf0, vf7x\n"
                                 "vmulax.xyz ACC, vf5, vf7x\n"
                                 "vmaddw.xyz vf5, vf6, vf8w\n"
                                 "sqc2 vf5, 0x0(%3)\n"
                                 :
                                 : "r"(t), "r"(a2), "r"(a1), "r"(&tmpA)
                                 : "memory");
            ret = func_000B69F0(a0, &tmpA, a2, work, *(int *)(work + 8) + (((bits >> 17) & 0x3FFF) << 3));
        } else {
            if (inQ == 0) {
                t = (limit - qv) / (pv - qv) - 0.0f;
                __asm__ __volatile__("qmtc2.ni %0, vf7\n"
                                     "lqc2 vf5, 0x0(%1)\n"
                                     "lqc2 vf6, 0x0(%2)\n"
                                     "vsubx.w vf8, vf0, vf7x\n"
                                     "vmulax.xyz ACC, vf5, vf7x\n"
                                     "vmaddw.xyz vf5, vf6, vf8w\n"
                                     "sqc2 vf5, 0x0(%3)\n"
                                     :
                                     : "r"(t), "r"(a1), "r"(a2), "r"(&tmpB)
                                     : "memory");
                a2 = &tmpB;
            }
            ret = func_000B69F0(a0, a1, a2, work, *(int *)(work + 8) + (((bits >> 17) & 0x3FFF) << 3));
        }
    }
    return ret;
}
#endif
