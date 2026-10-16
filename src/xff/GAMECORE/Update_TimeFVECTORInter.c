typedef int s128 __attribute__((mode(TI)));

typedef struct {
    s128 from;
    s128 to;
    s128 cur;
    float total;
    float rest;
} TimeFVectorInter;

extern char gcGlobalVar[];

void Update_TimeFVECTORInter(TimeFVectorInter *t)
{
    float r;

    if (0.0f < t->rest) {
        t->rest = t->rest - *(float *)(gcGlobalVar + 0x180);
        r = (t->total - t->rest) / t->total;
        __asm__ __volatile__("mfc1 $8, %3\n"
                             "qmtc2.ni $8, vf7\n"
                             "lqc2 vf5, 0x0(%1)\n"
                             "lqc2 vf6, 0x0(%2)\n"
                             "vsubx.w vf8, vf0, vf7x\n"
                             "vmulax.xyz ACC, vf5, vf7x\n"
                             "vmaddw.xyz vf5, vf6, vf8w\n"
                             "sqc2 vf5, 0x0(%0)\n"
                             : : "r"(&t->cur), "r"(&t->to), "r"(&t->from), "f"(r) : "$8", "memory");
        if (t->rest <= 0.0f)
            t->cur = t->to;
    }
}
