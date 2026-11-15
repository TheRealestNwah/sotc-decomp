/* Parked: 73 diffs, same size. Narga wall check: derives the facing axis from the layout quaternion (+0x13C) and the unit direction to the player's layout (data+0x407C), tests their dot against cos(f21 degrees), then ray-casts f20 units along the player direction (ClipCollisionDirectCallBack with getRealColJudgeFunc) and writes the verdict (1 wall hit within range, 2 too close, 3 no hit) plus the hit position and direction into the AI work at +0x5A80..+0x5AA0. VU0 runs match word for word. Remaining: the two vector pointers land in s1/s0 swapped (the Original has s0=+0x20, s1=+0x10; pinning them grows the frame), the cfc2 output register, and the operand register naming of the final distance run. */
#ifdef NONMATCHING
typedef int s128 __attribute__((mode(TI)));
typedef struct {
    float x, y, z, w;
} __attribute__((aligned(16))) Vec4;

extern char *GetSCRCharaAIWorkPtr(void);
extern char *getSCRDataCtrlWork(void *);
extern char *GetLayoutClass(void *);
extern int getPassageNum(void *);
extern float iosGetCosf(float);
extern int getColiGroupByUserPathWork(void *);
extern void *getRealColJudgeFunc(void *);
extern int ClipCollisionDirectCallBack(void *, void *, void *, int, int, int, int, void *, int);
extern int nico_GetGeometryPointerAttr(void *);

static inline void normalize(void *v)
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

void SCRFuncNargaWallCheckMain(void *obj, float f23, float f22, float f20, float f21)
{
    struct {
        Vec4 v10;
        Vec4 v20;
        Vec4 v30;
        char hit[0x50];
    } L;
    char *ai;
    char *data;
    char *lay;
    float cs;
    float dot;
    float d;
    int bits;
    int grp;
    char *s0;
    char *s1;

    ai = GetSCRCharaAIWorkPtr();
    data = getSCRDataCtrlWork(obj);
    lay = GetLayoutClass(obj);
    *(int *)(ai + 0x5AA0) = 0;
    if (getPassageNum(data) < 2) {
        s0 = (char *)&L.v20;
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
                             : : "r"(s0), "r"(*(char **)(lay + 0x13C)) : "memory");
        L.v20.y = 0.0f;
        normalize(s0);
        s1 = (char *)&L.v10;
        __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                             "lqc2 vf6, 0x0(%2)\n"
                             "vsub.xyzw vf7, vf5, vf6\n"
                             "sqc2 vf7, 0x0(%0)\n"
                             : : "r"(s1), "r"(*(char **)(*(char **)(data + 0x407C) + 0x134)), "r"(*(char **)(lay + 0x134)) : "memory");
        L.v10.y = 0.0f;
        normalize(s1);
        cs = iosGetCosf(f21 * 0.017453294f);
        __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                             "lqc2 vf6, 0x0(%2)\n"
                             "vaddw.x vf7, vf0, vf0w\n"
                             "vmul.xyz vf6, vf5, vf6\n"
                             "vaddax.x ACC, vf0, vf6x\n"
                             "vmadday.x ACC, vf7, vf6y\n"
                             "vmaddz.x vf6, vf7, vf6z\n"
                             "qmfc2.ni %0, vf6\n"
                             : "=&r"(bits) : "r"(s0), "r"(s1) : "memory");
        __asm__("mtc1 %1, %0" : "=f"(dot) : "r"(bits));
        if (cs < dot) {
            s0 = (char *)&L.v30;
            __asm__("mfc1 %0, %1" : "=r"(bits) : "f"(f20));
            __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                                 "qmtc2.ni %1, vf6\n"
                                 "vmulx.xyz vf5, vf5, vf6x\n"
                                 "sqc2 vf5, 0x0(%2)\n"
                                 : : "r"(s1), "r"(bits), "r"(s0) : "memory");
            __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                                 "lqc2 vf6, 0x0(%1)\n"
                                 "vadd.xyz vf5, vf5, vf6\n"
                                 "sqc2 vf5, 0x0(%0)\n"
                                 : : "r"(s0), "r"(*(char **)(lay + 0x134)) : "memory");
            L.v30.w = 1.0f;
            grp = getColiGroupByUserPathWork(data);
            if (ClipCollisionDirectCallBack(L.hit, *(char **)(lay + 0x134), s0, grp, 0, 0, 0, getRealColJudgeFunc(data), 0) != 0) {
                __asm__ __volatile__("lqc2 vf5, 0x0(%2)\n"
                                     "lqc2 vf6, 0x0(%1)\n"
                                     "vsub.xyzw vf7, vf5, vf6\n"
                                     "vmul.xz vf7, vf7, vf7\n"
                                     "vaddz.x vf7, vf7, vf7z\n"
                                     ".word 0x4A2703BD\n"
                                     "vwaitq\n"
                                     "cfc2.ni %0, $vi22\n"
                                     : "=&r"(bits) : "r"(*(char **)(lay + 0x134)), "r"(L.hit + 0x40) : "memory");
                __asm__("mtc1 %1, %0" : "=f"(d) : "r"(bits));
                if (d < f22) {
                    if (d < 20.0f) {
                        *(int *)(ai + 0x5AA0) = 2;
                    } else if ((nico_GetGeometryPointerAttr(L.hit) & 0x1E00000) != 0xA00000) {
                        if (f23 <= d) {
                            *(int *)(ai + 0x5AA0) = 1;
                            *(s128 *)(ai + 0x5A80) = *(s128 *)(L.hit + 0x40);
                            *(s128 *)(ai + 0x5A90) = *(s128 *)&L.v10;
                        }
                    }
                }
            } else {
                *(s128 *)(ai + 0x5A80) = *(s128 *)&L.v30;
                *(int *)(ai + 0x5AA0) = 3;
                *(s128 *)(ai + 0x5A90) = *(s128 *)&L.v10;
            }
        }
    }
}
#endif
