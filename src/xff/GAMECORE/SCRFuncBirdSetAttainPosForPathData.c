typedef struct {
    int unk0;
    int pts;
    int lines;
} PathInfo;

extern int GetSCRCharaAIWorkPtr(void);
extern char *GetLayoutClass(int);
extern PathInfo *getPathInfo(int);
extern int getPointDataFromEvent(int, int, int *);
extern short *getConnectLineArray(int, int);
extern short *getLineData(int, short);
extern float *getPointData(int, short);
extern void setAttainmentPos(int, int);

static inline void normalize3(float *v)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                         "vmul.xyz vf7, vf5, vf5\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         "vrsqrt Q, vf0w, vf7w\n"
                         "vwaitq\n"
                         "vmulq.xyz vf5, vf5, Q\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(v) : "memory");
}

static inline void sub4(float *d, float *a, float *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "sqc2 vf7, 0x0(%0)\n"
                         : : "r"(d), "r"(a), "r"(b) : "memory");
}

static inline float dot3(float *a, float *b)
{
    float r;
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vaddw.x vf7, vf0, vf0w\n"
                         "vmul.xyz vf6, vf5, vf6\n"
                         "vaddax.x ACC, vf0, vf6x\n"
                         "vmadday.x ACC, vf7, vf6y\n"
                         "vmaddz.x vf6, vf7, vf6z\n"
                         "qmfc2.ni $2, vf6\n"
                         "mtc1 $2, %0\n"
                         : "=f"(r) : "r"(a), "r"(b) : "$2");
    return r;
}

#ifdef NONMATCHING /* 122 diffs, 3 words short: bird path attain; loop/early-exit layout and saved registers */
void SCRFuncBirdSetAttainPosForPathData(int obj, int ev0, int ev1)
{
    int pts[2];
    int ids[2];
    float dot[16] __attribute__((aligned(16)));
    float d0[4] __attribute__((aligned(16)));
    float d1[4] __attribute__((aligned(16)));
    int work = GetSCRCharaAIWorkPtr() + 0x10;
    char *lay = GetLayoutClass(obj);
    PathInfo *info = getPathInfo(work);
    int i;

    pts[0] = getPointDataFromEvent(work, ev0, &ids[0]);
    pts[1] = getPointDataFromEvent(work, ev1, &ids[1]);
    if (pts[0] != 0 && pts[1] != 0) {
        for (i = 0; i < 2; i++) {
            short *line = getLineData(info->lines, *getConnectLineArray(info->pts, ids[i]));
            short next;
            float *p;

            if (line == 0)
                return;
            next = line[0];
            if (ids[i] == next)
                next = line[1];
            p = getPointData(info->pts, next);
            sub4(d0, (float *)pts[i], *(float **)(lay + 0x134));
            sub4(d1, p, (float *)pts[i]);
            normalize3(d0);
            normalize3(d1);
            dot[8 + i] = dot3(d0, d1);
        }
        if (dot[9] < dot[8]) {
            setAttainmentPos(work, pts[0]);
            return;
        }
        setAttainmentPos(work, pts[1]);
        return;
    }
}
#endif
