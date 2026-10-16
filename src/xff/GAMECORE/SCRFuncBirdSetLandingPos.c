typedef struct {
    float x, y, z, w;
} __attribute__((aligned(16))) Vec4;

extern char *GetSCRCharaAIWorkPtr(void *);
extern int getPointPosFromEvent(void *, int, Vec4 *);
extern void setAttainmentPosAndDir(void *, Vec4 *, Vec4 *);

void SCRFuncBirdSetLandingPos(void *obj, int from, int to)
{
    char *w = GetSCRCharaAIWorkPtr(obj) + 0x10;
    Vec4 p1;
    Vec4 p2;
    Vec4 dir;

    if (getPointPosFromEvent(w, from, &p1) && getPointPosFromEvent(w, to, &p2)) {
        __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                             "lqc2 vf6, 0x0(%2)\n"
                             "vsub.xyzw vf7, vf5, vf6\n"
                             "sqc2 vf7, 0x0(%0)\n"
                             : : "r"(&dir), "r"(&p1), "r"(&p2) : "memory");
        dir.y = 0.0f;
        __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                             "vmul.xyz vf7, vf5, vf5\n"
                             "vmulax.w ACC, vf0, vf7x\n"
                             "vmadday.w ACC, vf0, vf7y\n"
                             "vmaddz.w vf7, vf0, vf7z\n"
                             "vrsqrt Q, vf0w, vf7w\n"
                             "vwaitq\n"
                             "vmulq.xyz vf5, vf5, Q\n"
                             "sqc2 vf5, 0x0(%0)\n"
                             : : "r"(&dir) : "memory");
        dir.w = 1.0f;
        setAttainmentPosAndDir(w, &p1, &dir);
    }
}
