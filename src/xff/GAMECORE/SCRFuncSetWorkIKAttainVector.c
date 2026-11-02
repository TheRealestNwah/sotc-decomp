typedef struct {
    float x, y, z, w;
} __attribute__((aligned(16))) Vec4;

extern Vec4 YUnitVector;
extern char *getSCRDataCtrlWork(void *);
extern void *getPassageWork(char *, int);
extern char *GetLayoutClass(void *);
extern void GetQuaternionByAxisDirZY(Vec4 *, Vec4 *, Vec4 *);
extern void *getWormIKWork(void *);
extern void setWormIKAttainXVector(void *, Vec4 *);

static inline void vecNormalize(void *v)
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

void SCRFuncSetWorkIKAttainVector(void *obj)
{
    char *w = getSCRDataCtrlWork(obj);
    void *p = getPassageWork(w, 0);
    Vec4 v;
    Vec4 q;

    if (*(int *)(w + 0x4090) != 3 || p == 0)
        return;
    {
        char *l = GetLayoutClass(obj);

        __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                             "lqc2 vf6, 0x0(%2)\n"
                             "vsub.xyzw vf7, vf5, vf6\n"
                             "sqc2 vf7, 0x0(%0)\n"
                             : : "r"(&v), "r"(p), "r"(*(void **)(l + 0x134)) : "memory");
    }
    vecNormalize(&v);
    v.w = 1.0f;
    GetQuaternionByAxisDirZY(&q, &v, &YUnitVector);
    __asm__ __volatile__("lqc2 vf4, 0x0(%1)\n"
                         "vmul.xyzw vf5, vf4, vf4\n"
                         "vmr32.xyzw vf6, vf4\n"
                         "vmul.xyzw vf7, vf6, vf4\n"
                         "vmr32.xyzw vf6, vf6\n"
                         "vmul.xyzw vf8, vf6, vf4\n"
                         "vsubz.x vf6, vf7, vf7z\n"
                         "vaddx.y vf6, vf0, vf6x\n"
                         "vsuby.x vf6, vf0, vf5y\n"
                         "vsubz.x vf6, vf6, vf5z\n"
                         "vaddw.z vf6, vf8, vf8w\n"
                         "vsub.w vf6, vf6, vf6\n"
                         "vsub.w vf6, vf0, vf0\n"
                         "vadd.w vf5, vf0, vf0\n"
                         "vmulw.xyz vf6, vf6, vf5w\n"
                         "vaddw.x vf6, vf6, vf0w\n"
                         "sqc2 vf6, 0x0(%0)\n"
                         : : "r"(&v), "r"(&q) : "memory");
    setWormIKAttainXVector(getWormIKWork(obj), &v);
}
