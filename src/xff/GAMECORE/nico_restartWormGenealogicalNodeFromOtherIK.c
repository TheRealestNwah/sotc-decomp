typedef int s128 __attribute__((mode(TI)));
typedef float Vec4[4] __attribute__((aligned(16)));

typedef struct Node {
    s128 pos;
    s128 dir;
    s128 pad;
} Node;

extern int GetSCRCharaAIWorkPtr(int);

/* Parked: 76 words off. Structure and VU blocks follow the asm; left: register naming (original keeps the worm base copy in $t7, a 0x20 constant in $t8 and the node-flag base in $t3) and loop-counter scheduling. */
#ifdef NONMATCHING
void nico_restartWormGenealogicalNodeFromOtherIK(int *arg0)
{
    char *base = (char *)((GetSCRCharaAIWorkPtr(*arg0) + 0x41B3) & ~0xF);
    char *w = base + 0x12A0;
    s128 *src = (s128 *)(base + 0xA10);
    char *nrm = base + 0xC20;
    Vec4 tmpbuf;
    float *tmp = tmpbuf;
    int n;

    __asm__("" : "+r"(tmp));

    for (n = 31; n >= 0; n--) {
        __asm__ __volatile__("lqc2 vf4, 0x0(%0)\n"
                             "vmul.xyzw vf5, vf4, vf4\n"
                             "vmr32.xyzw vf6, vf4\n"
                             "vmul.xyzw vf7, vf6, vf4\n"
                             "vaddy.z vf6, vf0, vf7y\n"
                             "vsubw.z vf6, vf6, vf7w\n"
                             "vsubx.y vf6, vf0, vf5x\n"
                             "vsubz.y vf6, vf6, vf5z\n"
                             "vaddz.x vf6, vf7, vf7z\n"
                             "vsub.w vf6, vf0, vf0\n"
                             "vadd.w vf5, vf0, vf0\n"
                             "vmulw.xyz vf6, vf6, vf5w\n"
                             "vaddw.y vf6, vf6, vf0w\n"
                             "sqc2 vf6, 0x0(%1)\n"
                             : : "r"(nrm), "r"(tmp) : "memory");
        if (*(signed char *)(w + 0x60C) != 0) {
            Node *p = (Node *)w;
            char *flag = w + 0x60D;
            int i;
            for (i = 31; i >= 0; i--) {
                p->pos = *src;
                p->dir = *(s128 *)tmp;
                p = (Node *)((char *)p + 0x30);
                *flag++ = 1;
            }
            *(signed char *)(w + 0x60C) = 0;
        }
        {
            int idx = *(int *)(w + 0x604);
            Node *cur = (Node *)(w + idx * 0x30);
            Node *prev = (Node *)(w + ((idx + 31) % 32) * 0x30);
            float d;
            __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                                 "lqc2 vf6, 0x0(%2)\n"
                                 "vsub.xyzw vf7, vf5, vf6\n"
                                 "vmul.xyz vf7, vf7, vf7\n"
                                 "vaddy.x vf7, vf7, vf7y\n"
                                 "vaddz.x vf7, vf7, vf7z\n"
                                 "qmfc2.ni $2, vf7\n"
                                 "mtc1 $2, %0\n"
                                 : "=f"(d) : "r"(prev), "r"(cur) : "$2", "memory");
            idx = idx + 1;
            if (idx == 0x20)
                idx = 0;
            *(int *)(w + 0x604) = idx;
            *(signed char *)(w + 0xD + idx + 0x600) = 0;
        }
        *(s128 *)(w + *(int *)(w + 0x604) * 0x30) = *src;
        src -= 5;
        *(s128 *)(w + *(int *)(w + 0x604) * 0x30 + 0x10) = *(s128 *)tmp;
        nrm -= 0x10;
    }
    *(signed char *)(base + 0x1298) = 1;
}
#else
extern void nico_restartWormGenealogicalNodeFromOtherIK(int *arg0);
#endif
