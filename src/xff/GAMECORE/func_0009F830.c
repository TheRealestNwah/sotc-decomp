typedef struct { float x, y, z, w; } __attribute__((aligned(16))) FVec;

extern char gcGlobalVar[];
extern int isysGetThisSubThread(void);
extern void *memset(void *, int, unsigned int);
extern int AI_CheckNormZero(void *);
extern char *GetLayoutClass(int);
extern char *GetScriptCharacterClass(int);
extern int Kite_CmpPathPoint(void *, void *);
extern int *isysGroupForFirst(void *, int);
extern int *isysGroupForNext(int *, int);
extern void isysGroupForExit(int, int);

static inline void subV(void *out, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "sqc2 vf7, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline void normalizeXYZ(void *output, void *input)
{
    __asm__ __volatile__(".set noreorder\n"
        "lqc2 vf5, 0x0(%1)\n"
        "vmul.xyz vf7, vf5, vf5\n"
        "vmulax.w ACC, vf0, vf7x\n"
        "vmadday.w ACC, vf0, vf7y\n"
        "vmaddz.w vf7, vf0, vf7z\n"
        "vrsqrt Q, vf0w, vf7w\n"
        "vwaitq\n"
        "vmulq.xyz vf5, vf5, Q\n"
        "sqc2 vf5, 0x0(%0)\n"
        ".set reorder\n"
        : : "r"(output), "r"(input) : "memory");
}

static inline void crossV(void *out, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vopmula.xyz ACC, vf5, vf6\n"
                         "vopmsub.xyz vf7, vf6, vf5\n"
                         "vsub.w vf7, vf7, vf7\n"
                         "sqc2 vf7, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline float dotXYZ(void *a, void *b)
{
    float dot;
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vaddw.x vf7, vf0, vf0w\n"
                         "vmul.xyz vf6, vf5, vf6\n"
                         "vaddax.x ACC, vf0, vf6x\n"
                         "vmadday.x ACC, vf7, vf6y\n"
                         "vmaddz.x vf6, vf7, vf6z\n"
                         "qmfc2.ni $2, vf6\n"
                         "mtc1 $2, %0\n"
                         : "=f"(dot) : "r"(a), "r"(b) : "$2");
    return dot;
}

static int func_0009F830(char *w)
{
    FVec dir, side, up;
    int th = isysGetThisSubThread();
    int *g;
    int id;
    int res;
    char *o;

    memset(&up, 0, 0x10);
    up.y = *(int *)(w + 0x794) < 0 ? -1.0f : 1.0f;
    side = up;
    subV(&dir, w + 0x5B0, w + 0x590);
    dir.y = 0.0f;
    if (AI_CheckNormZero(&dir) != 0) {
        normalizeXYZ(&dir, &dir);
        crossV(&side, &side, &dir);
        if (dotXYZ(w + 0x240, &side) <= 0.0f)
            return 0;
    }
    if (*(int *)(w + 0x38) != 0) {
        if (AI_CheckNormZero(&dir) != 0) {
            subV(&up, *(void **)(GetLayoutClass(th) + 0x134), w + 0x590);
            up.y = 0.0f;
            normalizeXYZ(&up, &up);
            if (dotXYZ(&dir, &up) > 0.0f)
                return 0;
            if (dotXYZ(&side, &up) >= 0.0f)
                return 0;
        }
        if (*(float *)(w + 0x298) < *(float *)(w + 0x294))
            return 0;
        res = 1;
        id = 0;
        for (g = isysGroupForFirst(gcGlobalVar + 0x2BC, 0); g != 0; g = isysGroupForNext(g, 0)) {
            id = *g;
            o = *(char **)(GetScriptCharacterClass(id) + 0x1200);
            if (o != 0 && *(int *)o == 1 && *(int *)(o + 8) == *(int *)(w + 8)
                && *(int *)(o + 4) == *(int *)(w + 4) && *(int *)(o + 8) != -1
                && *(int *)(o + 0x26C) != 0x12) {
                if (Kite_CmpPathPoint(w + 0x640, o + 0x600) != 0)
                    res = -1;
                else if (Kite_CmpPathPoint(w + 0x660, o + 0x600) != 0)
                    res = -1;
                else {
                    if (*(int *)(w + 0x274) != *(int *)(o + 0x274))
                        res = 0;
                    if (Kite_CmpPathPoint(w + 0x600, o + 0x600) == 0)
                        res = 0;
                }
            }
        }
        if (id != 0)
            isysGroupForExit(id, 0);
        if (res == 0)
            return 0;
    } else {
        if (Kite_CmpPathPoint(*(char **)(w + 0x2C) + 0x600, w + 0x600) != 0)
            return 0;
        if (Kite_CmpPathPoint(*(char **)(w + 0x2C) + 0x600, w + 0x600) != 0
            && *(int *)(*(char **)(w + 0x2C) + 0x274) == 1)
            return 0;
    }
    return 1;
}
