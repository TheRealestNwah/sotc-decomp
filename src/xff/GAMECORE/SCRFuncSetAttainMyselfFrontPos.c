typedef struct {
    float x, y, z, w;
} __attribute__((aligned(16))) Vec4;

extern char *getSCRDataCtrlWork(void *);
extern char *GetLayoutClass(void *);
extern void setAttainmentPosAndLock(void *, Vec4 *);

static inline void vecNormalize(void *v)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)
"
                         "vmul.xyz vf7, vf5, vf5
"
                         "vmulax.w ACC, vf0, vf7x
"
                         "vmadday.w ACC, vf0, vf7y
"
                         "vmaddz.w vf7, vf0, vf7z
"
                         "vrsqrt Q, vf0w, vf7w
"
                         "vwaitq
"
                         "vmulq.xyz vf5, vf5, Q
"
                         "sqc2 vf5, 0x0(%0)
"
                         : : "r"(v) : "memory");
}

void SCRFuncSetAttainMyselfFrontPos(void *obj, float dist)
{
    char *w = getSCRDataCtrlWork(obj);
    char *l = GetLayoutClass(obj);
    Vec4 v;

    __asm__ __volatile__("lqc2 vf4, 0x0(%1)
"
                         "vmul.xyzw vf5, vf4, vf4
"
                         "vmr32.xyzw vf6, vf4
"
                         "vmul.xyzw vf7, vf6, vf4
"
                         "vmr32.xyzw vf6, vf6
"
                         "vmul.xyzw vf8, vf6, vf4
"
                         "vsubx.z vf6, vf0, vf5x
"
                         "vsuby.z vf6, vf6, vf5y
"
                         "vaddw.y vf6, vf7, vf7w
"
                         "vsuby.x vf6, vf8, vf8y
"
                         "vsub.w vf6, vf0, vf0
"
                         "vadd.w vf5, vf0, vf0
"
                         "vmulw.xyz vf6, vf6, vf5w
"
                         "vaddw.z vf6, vf6, vf0w
"
                         "sqc2 vf6, 0x0(%0)
"
                         : : "r"(&v), "r"(*(void **)(l + 0x13C)) : "memory");
    v.y = 0.0f;
    vecNormalize(&v);
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)
"
                         "qmtc2.ni %1, vf6
"
                         "vmulx.xyz vf5, vf5, vf6x
"
                         "sqc2 vf5, 0x0(%0)
"
                         : : "r"(&v), "r"(dist) : "memory");
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)
"
                         "lqc2 vf6, 0x0(%2)
"
                         "vadd.xyz vf5, vf5, vf6
"
                         "sqc2 vf5, 0x0(%0)
"
                         : : "r"(&v), "r"(&v), "r"(*(void **)(l + 0x134)) : "memory");
    v.w = 1.0f;
    setAttainmentPosAndLock(w, &v);
}
