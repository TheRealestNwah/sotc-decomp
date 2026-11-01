typedef int s128 __attribute__((mode(TI)));
extern char B_0018B7B0[], B_0018B7D0[];
extern int B_0018B804;
extern void GetMotionNodeQuaternionPosToolCoord(void *, void *, void *, int, int);
extern char *GetLayoutClass(void *);

void nico_player_pendulum_HandEffector(int *p)
{
    s128 q[2];
    void *obj = (void *)p[0];
    char *v = B_0018B7B0;
    GetMotionNodeQuaternionPosToolCoord(q, v, obj, p[5], 1);
    __asm__ __volatile__("lqc2 vf8, 0x0(%2)\n"
                         "lqc2 vf14, 0x0(%1)\n"
                         "lqc2 vf15, 0x10(%1)\n"
                         "lqc2 vf16, 0x20(%1)\n"
                         "lqc2 vf17, 0x30(%1)\n"
                         "vmulax.xyzw ACC, vf14, vf8x\n"
                         "vmadday.xyzw ACC, vf15, vf8y\n"
                         "vmaddaz.xyzw ACC, vf16, vf8z\n"
                         "vmaddw.xyzw vf10, vf17, vf8w\n"
                         "sqc2 vf10, 0x0(%0)\n"
                         : : "r"(&q[1]), "r"(p + 0x1C), "r"(v) : "memory");
    if (*(int *)(GetLayoutClass(obj) + 0x124) != 0) {
        int idx = p[5] & 0xFFFEFFFF;
        char *m = (char *)p[4];
        char *lc = GetLayoutClass(obj);
        char *s = (char *)((idx << 6) + *(int *)(m + 0x24)) + 0x10;
        __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                             "lqc2 vf6, 0x0(%2)\n"
                             "vmul.xyz vf5, vf5, vf6\n"
                             "sqc2 vf5, 0x0(%0)\n"
                             : : "r"(B_0018B7D0), "r"(s), "r"(lc + 0x90) : "memory");
        B_0018B804 = 1;
    } else {
        B_0018B804 = 0;
    }
}
