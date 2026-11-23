/* player_HellDangerDetect: Parked attempt, 21 diffs, same size.
 * Remaining: the kind==2 block keeps &dir (sp+0x50) in s1 where the Original
 * rematerializes it after SetQuaternionByAxisRotateVWithNoRegularize, and
 * col / the -1 loop constant / &normal sit in swapped callee-saved registers.
 */
#ifdef NONMATCHING
typedef int s128 __attribute__((mode(TI)));
typedef union {
    s128 q;
    float f[4];
} Vec4;

extern char *ScriptCtrlDef_SCRPlayerHellDanger;
extern int PHMotionKind_PLAYER_RUN;
extern int PHMotionKind_PLAYER_RUN_WITH_SWORD;
extern Vec4 YUnitVector;
extern char *GetCharacterClass(int);
extern void CharaCtrlResetScriptCtrlStatus(int, int);
extern void CharaCtrlSetScriptCtrlStatus(int, int);
extern unsigned long long *GetCollisionDBAttributeAdr(void *);
extern int func_0007DCB8(void *, void *, void *, void *, void *, float);
extern float GetTurnYAngleFromGlobalDir(void *, void *);
extern void SetQuaternionByAxisRotateVWithNoRegularize(void *, short, void *);
extern void SetLayoutClassRootQuaternion(void *, void *);
extern void GetPlaneFittingPoint(void *, void *, void *);
extern int ClipCollisionFinder(void *, void *, void *, void *);
extern void CopyGeometryPointer(void *, void *);

static Vec4 D_0017AE90 = {{0}};

static inline void transformPoint(void *out, void *q, void *t, void *v)
{
    __asm__ __volatile__("lqc2 vf8, 0x0(%2)\n"
                         "lqc2 vf18, 0x0(%1)\n"
                         "vmove.w vf18, vf0\n"
                         "vaddw.xyz vf12, vf0, vf0w\n"
                         "lqc2 vf11, 0x0(%0)\n"
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
                         : : "r"(q), "r"(t), "r"(v));
    __asm__ __volatile__("vmulax.xyzw ACC, vf14, vf8x\n"
                         "vmadday.xyzw ACC, vf15, vf8y\n"
                         "vmaddaz.xyzw ACC, vf16, vf8z\n"
                         "vmaddw.xyzw vf10, vf18, vf8w\n"
                         "sqc2 vf10, 0x0(%0)\n"
                         : : "r"(out) : "memory");
}

static inline void vscale(void *out, void *v, float s)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "qmtc2.ni %2, vf6\n"
                         "vmulx.xyz vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(v), "r"(s) : "memory");
}

static inline void vadd3(void *out, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vadd.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline void vsub3(void *out, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline void vsub4(void *out, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "sqc2 vf7, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline void quatMul(void *out, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf11, 0x0(%1)\n"
                         "lqc2 vf12, 0x0(%2)\n"
                         "vmul.xyzw vf13, vf11, vf12\n"
                         "vaddy.x vf13, vf13, vf13y\n"
                         "vaddz.x vf13, vf13, vf13z\n"
                         "vsubx.w vf13, vf13, vf13x\n"
                         "vmulw.xyz vf14, vf12, vf11w\n"
                         "vmulw.xyz vf15, vf11, vf12w\n"
                         "vopmula.xyz ACC, vf12, vf11\n"
                         "vopmsub.xyz vf16, vf11, vf12\n"
                         "vadd.xyz vf13, vf14, vf15\n"
                         "vadd.xyz vf13, vf13, vf16\n"
                         "sqc2 vf13, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline void quatDir(void *out, void *q)
{
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
                         : : "r"(out), "r"(q) : "memory");
}

static inline float dot3(void *a, void *b)
{
    float d;
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vaddw.x vf7, vf0, vf0w\n"
                         "vmul.xyz vf6, vf5, vf6\n"
                         "vaddax.x ACC, vf0, vf6x\n"
                         "vmadday.x ACC, vf7, vf6y\n"
                         "vmaddz.x vf6, vf7, vf6z\n"
                         "qmfc2.ni $2, vf6\n"
                         "mtc1 $2, %0\n"
                         : "=f"(d) : "r"(a), "r"(b) : "$2");
    return d;
}

static inline int detect(int *col, void *out, void *normal, void *a, void *b)
{
    int n;
    char *p;

    n = col[0];
    if (col[1] < n)
        n = col[1];
    if (n != 0) {
    p = (char *)col[3];
    while (n-- != 0) {
        if (*(int *)p != 0) {
            if ((*GetCollisionDBAttributeAdr(p) & 0xF80000000ULL) == 0xA80000000ULL) {
                if (func_0007DCB8(out, normal, a, b, p, 0.0f))
                    return 1;
            }
        }
        p += 8;
    }
    }
    return 0;
}

void player_HellDangerDetect(int obj, char *work)
{
    Vec4 hit;
    Vec4 normal;
    Vec4 end;
    Vec4 neg;
    Vec4 rq;
    Vec4 dir;
    Vec4 tmp;
    Vec4 cp;
    char clip[0x50];
    char *chr;
    int *col;
    int m;
    int kind;
    float d;
    void *q;
    short a;
    Vec4 *r;
    float f;
    Vec4 *off;

    chr = GetCharacterClass(obj);
    CharaCtrlResetScriptCtrlStatus(obj, *(int *)(ScriptCtrlDef_SCRPlayerHellDanger + 4));
    m = *(int *)(chr + 0x1C0);
    if (m != 0 && (m == PHMotionKind_PLAYER_RUN || m == PHMotionKind_PLAYER_RUN_WITH_SWORD))
        f = 0.855f;
    else
        f = 0.25f;
    off = &D_0017AE90;
    off->f[2] = f;
    transformPoint(&end, *(void **)(chr + 0x13C), *(void **)(chr + 0x134), off);
    col = (int *)(chr + 0xE20);
    if (detect(col, &hit, &normal, work + 0x50, &end))
        kind = 1;
    else
        kind = detect(col, &hit, &normal, work + 0x50, *(void **)(chr + 0x134)) << 1;
    if (kind == 0)
        return;
    /* Permuter find: the redundant branch shifts register allocation. */
    if (chr)
        vscale(&neg, &normal, -1.0f);
    else
        vscale(&neg, &normal, -1.0f);
    if (kind == 2) {
        d = GetTurnYAngleFromGlobalDir(*(void **)(chr + 0x13C), &neg);
        r = &rq;
        a = (int)(d * 32768.0f / 180.0f);
        q = *(void **)(chr + 0x13C);
        SetQuaternionByAxisRotateVWithNoRegularize(&dir, -a, &YUnitVector);
        quatMul(r, q, &dir);
        SetLayoutClassRootQuaternion(chr, r);
        GetPlaneFittingPoint(&hit, &normal, *(void **)(chr + 0x134));
        vscale(&tmp, &normal, D_0017AE90.f[2]);
        vadd3(&hit, &hit, &tmp);
    } else {
        quatDir(&dir, *(void **)(chr + 0x13C));
        d = dot3(&neg, &dir);
        if (d < 0.0f ? -0.4f < d : d < 0.4f) {
            vscale(&tmp, &normal, 0.1f);
            vadd3(&hit, &hit, &tmp);
        }
        vsub4(&tmp, &end, *(void **)(chr + 0x134));
        vsub3(&hit, &hit, &tmp);
    }
    cp.q = hit.q;
    tmp.q = hit.q;
    cp.f[1] = cp.f[1] - 1.0f;
    if (ClipCollisionFinder(clip, &tmp, &cp, col)) {
        *(s128 *)(work + 0x60) = neg.q;
        CopyGeometryPointer(work + 0x70, clip);
        CharaCtrlSetScriptCtrlStatus(obj, *(int *)(ScriptCtrlDef_SCRPlayerHellDanger + 4));
    }
}
#endif
