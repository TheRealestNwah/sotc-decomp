typedef struct {
    float x, y, z, w;
} __attribute__((aligned(16))) Vec4;

extern char *getSCRDataCtrlWork(void *);
extern char *GetLayoutClass(void *);

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

extern void *getColiGroupByUserPathWork(void *);
extern void *getRealColJudgeFunc(void *);
extern int ClipCollisionDirectCallBack(void *, void *, void *, void *, int, int, int, void *, int);
extern long nico_GetGeometryPointerAttr(void *);

int SCRConditionNargaStruggleStart(void *obj, float dist)
{
    char *w = getSCRDataCtrlWork(obj);
    char *l = GetLayoutClass(obj);
    Vec4 v;
    char buf[0x50];
    void *grp;

    __asm__ __volatile__("lqc2 vf4, 0x0(%1)\n"
                         "vmul.xyzw vf5, vf4, vf4\n"
                         "vmr32.xyzw vf6, vf4\n"
                         "vmul.xyzw vf7, vf6, vf4\n"
                         "vmr32.xyzw vf6, vf6\n"
                         "vmul.xyzw vf8, vf6, vf4\n"
                         "vsubx.z vf6, vf0, vf5x\n"
                         "vsuby.z vf6, vf6, vf5y\n"
                         "vaddw.y vf6, vf7, vf7w\n"
                         "vsuby.x vf6, vf8, vf8y\n"
                         "vsub.w vf6, vf0, vf0\n"
                         "vadd.w vf5, vf0, vf0\n"
                         "vmulw.xyz vf6, vf6, vf5w\n"
                         "vaddw.z vf6, vf6, vf0w\n"
                         "sqc2 vf6, 0x0(%0)\n"
                         : : "r"(&v), "r"(*(void **)(l + 0x13C)) : "memory");
    v.y = 0.0f;
    vecNormalize(&v);
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                         "qmtc2.ni %1, vf6\n"
                         "vmulx.xyz vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(&v), "r"(dist) : "memory");
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vadd.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(&v), "r"(&v), "r"(*(void **)(l + 0x134)) : "memory");
    v.w = 1.0f;
    grp = getColiGroupByUserPathWork(w);
    if (ClipCollisionDirectCallBack(buf, *(void **)(l + 0x134), &v, grp, 0, 0, 0, getRealColJudgeFunc(w), 0)) {
        if ((nico_GetGeometryPointerAttr(buf) & 0x1E00000) == 0x200000 ||
            (nico_GetGeometryPointerAttr(buf) & 0x1E00000) == 0x800000 ||
            (nico_GetGeometryPointerAttr(buf) & 0x1E00000) == 0xA00000) {
            return 1;
        }
    }
    return 0;
}
