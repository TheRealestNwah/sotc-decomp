extern char *GetSCRCharaAIWorkPtr(void *);
extern char *GetLayoutClass(void *);
extern float *getPointDataFromEvent(void *, int, int *);
extern void setAttainmentPos(void *, float *);

static inline float dist_xz(float *a, float *b)
{
    float d;
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "vmul.xz vf7, vf7, vf7\n"
                         "vaddz.x vf7, vf7, vf7z\n"
                         "qmfc2.ni $2, vf7\n"
                         "mtc1 $2, %0\n"
                         : "=f"(d) : "r"(a), "r"(b) : "$2");
    return d;
}

void SCRFuncBirdSetAttainFarPosForPathData(void *obj, int a, int b)
{
    char *work = GetSCRCharaAIWorkPtr(obj);
    char *w;
    char *lc = GetLayoutClass(obj);
    float *p[2];
    int tmp[2];

    w = work + 0x10;
    p[0] = getPointDataFromEvent(w, a, &tmp[0]);
    p[1] = getPointDataFromEvent(w, b, &tmp[1]);
    if (p[0]) {
        if (!p[1]) {
            setAttainmentPos(w, p[0]);
        } else {
            float *me = *(float **)(lc + 0x134);
            float d0 = dist_xz(p[0], me);
            float d1 = dist_xz(p[1], me);
            if (d1 < d0)
                setAttainmentPos(w, p[0]);
            else
                setAttainmentPos(w, p[1]);
        }
    }
}
