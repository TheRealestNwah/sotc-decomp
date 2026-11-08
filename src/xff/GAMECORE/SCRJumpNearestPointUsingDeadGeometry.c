typedef float Vec4[4] __attribute__((aligned(16)));
typedef struct { long long x, y; } Pair;

extern char *GetSCRCharaAIWorkPtr(void);
extern int getDeadPosAndQuaternion(void *, void *, void *, void *, int, float);
extern char *GetCharacterClass(void *);
extern void ForceUnparentLayoutObj(void *);
extern void ResetCharacterClassIKInfo(void *);
extern void ResetCharacterClassDynamicsElement(void *);
extern void ResetCharacterClassPositionMemoryInfo(void *);
extern void SetObjectGeo(void *, void *, void *);
extern void *memset(void *, int, unsigned int);
extern int ClipCollisionDirect(void *, void *, void *, int);
extern void ParentLayoutObj(void *, void *);
extern void SetCharacterObjDemoCutFinishFlag(void *, int);

/* Parked: ~54 words differ; the original rematerializes the matrix address (121 words vs 120) and orders the vd0 copy differently. */
#ifdef NONMATCHING
static inline void mkMat(float *mat, float *q)
{
    __asm__ __volatile__("vaddw.xyz vf12, vf0, vf0w\n"
                             "lqc2 vf11, 0x0(%1)\n"
                             "vmr32.w vf14, vf0\n"
                             "vmr32.w vf15, vf0\n"
                             "vmr32.w vf16, vf0\n"
                             "vopmula.xyz ACC, vf11, vf12\n"
                             "vmadd.xyz vf11, vf0, vf0\n"
                             "vmadd.xyz vf10, vf11, vf12\n"
                             "vmul.xyz vf13, vf11, vf10\n"
                             "vopmula.xyz ACC, vf11, vf10\n"
                             "vmaddw.xyz vf15, vf10, vf11w\n"
                             "vmsubw.xyz vf16, vf10, vf11w\n"
                             "vopmula.xyz ACC, vf13, vf12\n"
                             "vmadd.xyz vf17, vf13, vf12\n"
                             "vopmula.xyz ACC, vf15, vf12\n"
                             "vmadd.xyz vf15, vf0, vf0\n"
                             "vsub.xyz vf14, vf12, vf17\n"
                             "vmove.yz vf17, vf14\n"
                             "vmove.y vf14, vf16\n"
                             "vmove.y vf16, vf15\n"
                             "vmove.y vf15, vf17\n"
                             "vmove.z vf14, vf15\n"
                             "vmove.z vf15, vf16\n"
                             "vmove.z vf16, vf17\n"
                             "sqc2 vf14, 0x0(%0)\n"
                             "sqc2 vf15, 0x10(%0)\n"
                             "sqc2 vf16, 0x20(%0)\n"
                             : : "r"(mat), "r"(q) : "memory");
    __asm__ __volatile__("sqc2 vf0, 0x0(%0)\n" : : "r"(mat + 12) : "memory");
}

static inline void xformPos(float *mat, float *v)
{
    __asm__ __volatile__("lqc2 vf8, 0x0(%1)\n"
                             "lqc2 vf14, 0x0(%0)\n"
                             "lqc2 vf15, 0x10(%0)\n"
                             "lqc2 vf16, 0x20(%0)\n"
                             "lqc2 vf17, 0x30(%0)\n"
                             "vmulax.xyzw ACC, vf14, vf8x\n"
                             "vmadday.xyzw ACC, vf15, vf8y\n"
                             "vmaddaz.xyzw ACC, vf16, vf8z\n"
                             "vmaddw.xyzw vf10, vf17, vf8w\n"
                             "sqc2 vf10, 0x0(%1)\n"
                             : : "r"(mat), "r"(v) : "memory");
}

static inline void vecAdd(float *out, float *a, float *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                             "lqc2 vf6, 0x0(%2)\n"
                             "vadd.xyz vf5, vf5, vf6\n"
                             "sqc2 vf5, 0x0(%0)\n"
                             : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline void vecSubSub(float *out, float *a, float *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                             "lqc2 vf6, 0x0(%2)\n"
                             "vsub.xyz vf5, vf5, vf6\n"
                             "sqc2 vf5, 0x0(%0)\n"
                             "lqc2 vf5, 0x0(%0)\n"
                             "lqc2 vf6, 0x0(%2)\n"
                             "vsub.xyz vf5, vf5, vf6\n"
                             "sqc2 vf5, 0x0(%0)\n"
                             : : "r"(out), "r"(a), "r"(b) : "memory");
}

int SCRJumpNearestPointUsingDeadGeometry(void *obj)
{
    struct { Vec4 q; Vec4 pos; char buf[0x50]; Vec4 a1; Vec4 a2; Vec4 mat[4]; Vec4 vd0; Pair ve0; } L;
    char *chr;
    float *pos;

    if (getDeadPosAndQuaternion(obj, GetSCRCharaAIWorkPtr() + 0x10, pos = L.pos, L.q, 1, 600.0f) != 0) {
        chr = GetCharacterClass(obj);
        ForceUnparentLayoutObj(obj);
        ResetCharacterClassIKInfo(chr);
        ResetCharacterClassDynamicsElement(chr);
        ResetCharacterClassPositionMemoryInfo(chr);
        SetObjectGeo(obj, L.q, pos);
        memset(&L.ve0, 0, 0x10);
        ((float *)&L.ve0)[1] = *(float *)(chr + 0xE34);
        ((Pair *)L.vd0)->y = L.ve0.y;
        ((Pair *)L.vd0)->x = L.ve0.x;
        mkMat((float *)L.mat, L.q);
        xformPos((float *)L.mat, L.vd0);
        vecAdd(L.a1, pos, L.vd0);
        vecSubSub(L.a2, pos, L.vd0);
        {
            char *p = L.buf;
            if (ClipCollisionDirect(p, L.a1, L.a2, *(int *)(chr + 0xE38) + *(short *)(chr + 0x370) * 4) != 0)
                ParentLayoutObj(obj, p);
        }
        SetCharacterObjDemoCutFinishFlag(obj, 1);
    }
    return 0;
}
#else
extern int SCRJumpNearestPointUsingDeadGeometry(void *obj);
#endif
