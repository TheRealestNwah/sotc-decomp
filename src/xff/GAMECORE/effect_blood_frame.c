typedef int s128 __attribute__((mode(TI)));

typedef struct {
    s128 col;
    s128 add;
    int life;
    char *offset;
    char pad28[0x8];
} BloodWork;

extern int D_0017A9DC;

void effect_blood_frame(BloodWork *w, int base)
{
    int i;

    for (i = 0; i < D_0017A9DC; i++) {
        BloodWork *p = &w[i];
        char *o = p->offset;
        if (o != 0) {
            int c;
            __asm__ __volatile__("lqc2 $vf24, 0x0(%1)\n"
                                 "lqc2 $vf25, 0x0(%2)\n"
                                 "vadd.xyz $vf24, $vf24, $vf25\n"
                                 "vmax.xyz $vf24, $vf24, $vf0\n"
                                 "pceqw $8, $0, $0\n"
                                 "psrlw $9, $8, 24\n"
                                 "qmtc2.ni $9, $vf23\n"
                                 "vitof0.xyz $vf23, $vf23\n"
                                 "vmini.xyz $vf24, $vf24, $vf23\n"
                                 "sqc2 $vf24, 0x0(%1)\n"
                                 "vftoi0.xyzw $vf26, $vf24\n"
                                 "qmfc2.ni $8, $vf26\n"
                                 "ppach $10, $0, $8\n"
                                 "ppacb %0, $0, $10\n"
                                 : "=r"(c) : "r"(&p->col), "r"(&p->add) : "$8", "$9", "$10", "memory");
            *(int *)(o + base) = c;
            if (--p->life <= 0)
                p->offset = 0;
        }
    }
}
