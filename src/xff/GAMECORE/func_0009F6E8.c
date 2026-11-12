typedef struct { char pad[0xD0]; float d0; float d4; float d8; } Range;

#ifdef NONMATCHING /* 7 diffs: even with the barrier, gcc turns the final a0 ? 1 : 0 into sltu instead of the original bnez/li 1/li 0, which shifts branch offsets and puts the 0x38 load in $v1 */
static int func_0009F6E8(char *c)
{
    float f1;
    float dist;
    int st;
    int a0;
    int v1;

    if (*(int *)(c + 0x288) == 0)
        return 0;
    st = *(int *)(c + 0x274);
    if (st != 2 && st != 4 && st != 8 && st != 6)
        return 1;
    if (*(int *)(c + 0x38) != 0)
        return 0;
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
    if (f1 > 10.0f && dist < (*(Range **)(c + 0x20))->d8)
        a0 = 1;
    else if (f1 > 2.0f && dist < (*(Range **)(c + 0x20))->d4)
        a0 = 1;
    else if (f1 <= 2.0f && (v1 = dist < (*(Range **)(c + 0x20))->d0) != 0)
        a0 = 1;
    else {
        a0 = 0;
        if (st == 8 && *(int *)(c + 0x798) == 0)
            a0 = *(float *)(c + 0x90) < 50.0f;
    }
    __asm__("" : "+r"(a0));
    return a0 ? 1 : 0;
}
#endif
