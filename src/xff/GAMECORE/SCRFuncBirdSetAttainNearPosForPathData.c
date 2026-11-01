extern char *GetSCRCharaAIWorkPtr(void *);
extern char *GetLayoutClass(void *);
extern char *getPointDataFromEvent(char *, int, int *);
extern void setAttainmentPos(char *, char *);

static inline float distXZ2(char *a, char *b)
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

void SCRFuncBirdSetAttainNearPosForPathData(void *obj, int ev0, int ev1)
{
    char *pt[2];
    int idx[2];
    char *w = GetSCRCharaAIWorkPtr(obj);
    char *lc = GetLayoutClass(obj);
    char *pos;

    pt[0] = getPointDataFromEvent(w + 0x10, ev0, &idx[0]);
    pt[1] = getPointDataFromEvent(w + 0x10, ev1, &idx[1]);
    if (pt[0] == 0)
        return;
    if (pt[1] == 0) {
        setAttainmentPos(w + 0x10, pt[0]);
        return;
    }
    pos = *(char **)(lc + 0x134);
    if (distXZ2(pt[0], pos) < distXZ2(pt[1], pos))
        setAttainmentPos(w + 0x10, pt[0]);
    else
        setAttainmentPos(w + 0x10, pt[1]);
}
