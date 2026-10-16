extern char *getSCRDataCtrlWork(void *);
extern float *getGoalPointDataByAreaIdx(char *, int, int);
extern char *GetLayoutClass(void *);

int SCRConditionLessLengthXZPlayerFromGp(void *actor, float dist)
{
    char *w = getSCRDataCtrlWork(actor);
    float *g = getGoalPointDataByAreaIdx(w, *(int *)(w + 0x3C90), *(int *)(w + 0x3C8C));
    float d;

    if (g == 0)
        return 0;
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "vmul.xz vf7, vf7, vf7\n"
                         "vaddz.x vf7, vf7, vf7z\n"
                         "vsqrt Q, vf7x\n"
                         "vwaitq\n"
                         "cfc2 $2, $vi22\n"
                         "mtc1 $2, %0\n"
                         : "=f"(d)
                         : "r"(*(float **)(GetLayoutClass(actor) + 0x134)), "r"(g)
                         : "$2");
    return d <= dist;
}
