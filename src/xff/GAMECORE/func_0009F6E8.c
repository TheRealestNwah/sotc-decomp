typedef struct { char pad[0xD0]; float d0; float d4; float d8; } Range;

#ifdef NONMATCHING /* 36 diffs: the final ret=1/ret=0 on a0 becomes sltu instead of the original's delay-slot ret=1; 2.0f constant lands in $f3 instead of reloaded $f0; v0/v1 numbering */
static int func_0009F6E8(char *c)
{
    float f1;
    float dist;
    int st;
    register int ret __asm__("$2");
    int a0;
    int v1;

    ret = 0;
    if (*(int *)(c + 0x288) != 0 &&
        ((st = *(int *)(c + 0x274)) == 2 || st == 4 || st == 8 || (ret = 1, st == 6))) {
        ret = 0;
        if (*(int *)(c + 0x38) == 0) {
            f1 = *(float *)(c + 0x324);
            __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                                 "lqc2 vf6, 0x0(%2)\n"
                                 "vsub.xyzw vf7, vf5, vf6\n"
                                 "vmul.xyz vf7, vf7, vf7\n"
                                 "vmulax.w ACC, vf0, vf7x\n"
                                 "vmadday.w ACC, vf0, vf7y\n"
                                 "vmaddz.w vf7, vf0, vf7z\n"
                                 "vsqrt Q, vf7w\n"
                                 "vwaitq\n"
                                 "cfc2.ni $2, $vi22\n"
                                 "mtc1 $2, %0\n"
                                 : "=f"(dist) : "r"(c + 0x600), "r"(c + 0x50) : "$2", "memory");
            if (!(f1 > 10.0f) || (a0 = 1, !(dist < (*(Range **)(c + 0x20))->d8))) {
                if (f1 > 2.0f) {
                    a0 = 1;
                    if (!(dist < (*(Range **)(c + 0x20))->d4))
                        goto block11;
                } else {
                block11:
                    if (f1 <= 2.0f) {
                        v1 = 1;
                        if (!(dist < (*(Range **)(c + 0x20))->d0))
                            v1 = 0;
                        a0 = 1;
                        if (v1 == 0)
                            goto block16;
                    } else {
                    block16:
                        a0 = 0;
                        if (st == 8 && *(int *)(c + 0x798) == 0) {
                            a0 = 1;
                            if (!(*(float *)(c + 0x90) < 50.0f))
                                a0 = 0;
                        }
                    }
                }
            }
            ret = 1;
            if (a0 == 0)
                ret = 0;
        }
    }
    return ret;
}
#endif
