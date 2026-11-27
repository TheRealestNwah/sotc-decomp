extern char gcGlobalVar[];
extern int isysGetThisSubThread(void);
extern char *GetLayoutClass(int);
extern char *GetCharacterClass(int);
extern int ClipCollisionDirectCallBack(void *, void *, void *, void *, int (*)(), int, int, int (*)(), int);
extern void *GetGeometryPointerCollisionDB(void *, int);
extern char *GetCollisionDBPlane(void *);
extern void AI_GetNegaVector(void *, void *);
extern int AI_JudgeNotCharaObjFunc();
extern int AI_JudgeColAttrFunc();
typedef int s128 __attribute__((mode(TI)));

/* Parked: 11 diffs (same size, 133 words). Pinning cc to $s4 fixes the
 * callee-saved rotation; pinning the clip helper's result to $a1 puts it
 * where the Original keeps it. Remaining: the ClipCollisionDirectCallBack
 * a0 = sp+0x40 setup comes last instead of right after a1, the post-call
 * a0 = sp+0x40 lands in the jal delay slot instead of before the beqz, and
 * the 0.5f constant is loaded after the plane lq/sq instead of before. */
#ifdef NONMATCHING
static inline int clipTarget(void *p, void *tgt, s128 *out, s128 *plane)
{
    char geom[0x50] __attribute__((aligned(16)));
    register int r __asm__("$5") = 0;
    if (ClipCollisionDirectCallBack(geom, p, tgt, gcGlobalVar + 0x230, AI_JudgeNotCharaObjFunc, 0, 0, AI_JudgeColAttrFunc, 0) != 0) {
        *plane = *(s128 *)GetCollisionDBPlane(GetGeometryPointerCollisionDB(geom, 0));
        *out = *(s128 *)(geom + 0x40);
        r = 1;
    }
    return r;
}

static int func_000B4690(char *a, s128 *out, s128 *plane)
{
    float tgt[4] __attribute__((aligned(16)));
    float diff[4] __attribute__((aligned(16)));
    float push[4] __attribute__((aligned(16)));
    char *p;
    int th = isysGetThisSubThread();
    char *lc = GetLayoutClass(th);
    register char *cc __asm__("$20") = GetCharacterClass(th);
    float eps = 0.05f;
    float len;
    int ok;

    p = a + 0x50;
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%3)\n"
                         "lqc2 vf7, 0x0(%3)\n"
                         "vmul.xyz vf7, vf7, vf7\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         ".word 0x4BA703BD\n"
                         "vwaitq\n"
                         "cfc2.ni $2, $vi22\n"
                         "mtc1 $2, %0\n"
                         "lqc2 vf5, 0x0(%3)\n"
                         "vmul.xyz vf7, vf5, vf5\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         "vrsqrt Q, vf0w, vf7w\n"
                         "vwaitq\n"
                         "vmulq.xyz vf5, vf5, Q\n"
                         "sqc2 vf5, 0x0(%3)\n"
                         : "=f"(len) : "r"(*(char **)(lc + 0x134)), "r"(p), "r"(diff) : "$2", "memory");
    len += eps;
    __asm__ __volatile__("mfc1 $2, %2\n"
                         "lqc2 vf5, 0x0(%1)\n"
                         "qmtc2.ni $2, vf6\n"
                         "vmulx.xyzw vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(push), "r"(diff), "f"(len) : "$2", "memory");
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                         "lqc2 vf6, 0x0(%1)\n"
                         "vadd.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%2)\n"
                         : : "r"(p), "r"(push), "r"(tgt) : "memory");
    ok = clipTarget(p, tgt, out, plane);
    if (ok != 0) {
        AI_GetNegaVector(push, diff);
        __asm__ __volatile__("mfc1 $2, %1\n"
                             "lqc2 vf5, 0x0(%0)\n"
                             "qmtc2.ni $2, vf6\n"
                             "vmulx.xyzw vf5, vf5, vf6x\n"
                             "sqc2 vf5, 0x0(%0)\n"
                             : : "r"(push), "f"(eps) : "$2", "memory");
        __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                             "lqc2 vf6, 0x0(%1)\n"
                             "vadd.xyz vf5, vf5, vf6\n"
                             "sqc2 vf5, 0x0(%0)\n"
                             : : "r"(out), "r"(push) : "memory");
        return 1;
    }
    if (*(int *)(cc + 0xFF0) != 0 && *(float *)(cc + 0x1004) < *(float *)(*(char **)(lc + 0x134) + 4)) {
        do {
            *out = *(s128 *)(cc + 0x1000);
            *plane = *(s128 *)GetCollisionDBPlane(cc + 0xFF8);
        } while (0);
        {
            float h = 0.5f;
            return h < *(float *)((char *)plane + 4);
        }
    }
    return 0;
}
#endif
