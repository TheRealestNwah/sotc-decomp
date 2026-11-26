/* Parked: 991 of 1004 words (13 short), same structure. Sheath sword script: waits for the action flag, then each frame places the sheath from the horse/player bones (collision checks against the horse and clip finders), limits the turn rate of the sheath quaternion, and waits on the frame counter. The sheathPos helper and the tgt/a1D0 pointer variables reproduce the Original's early POS load and the fp/s6 bases. Remaining: register allocation. The Original keeps horse in s3 and hoists sp+0x40/0x1C0/0x150/0x1D0/0x1F0 into fp/s5/s7/s6/s4, rematerializing the other stack addresses at each use; this version spills horse and hoists a different set, and hoists gcGlobalVar out of the wait loop. Pinning the pointers to the Original's registers made it worse (981 words). */
#ifdef NONMATCHING
typedef int s128 __attribute__((mode(TI)));
typedef union { struct { float x, y, z, w; } v; s128 q; } Vec;
typedef struct { float x, y, z, w; } __attribute__((aligned(8))) F4;
typedef struct { int pad[2]; int x8; } SkelDef;

extern char gcGlobalVar[];
extern SkelDef *SkelFocusDef_PLAYER_SHEATH;
extern SkelDef *SkelFocusDef_PLAYER_SHEATH3;
extern SkelDef *SkelFocusDef_PLAYER_SUNE_L;
extern void *isysGetThisSubThread(void);
extern char *GetLayoutClass(void *);
extern void *GetLayoutParentObj(char *);
extern char **GetAnimationClass(void *);
extern char *GetCharacterClass(void *);
extern void UpdateLayoutClassParentGeometry(char *, int, int);
extern void UpdateLayoutClassPastSimpleGeometry(char *);
extern void UpdateLayoutClassSimpleGeometry(char *, float);
extern int nico_GetPlayerCharacterRidingHorseObject(void *);
extern void GetMotionNodeQuaternionPos(void *, void *, void *, int, int);
extern void GetMotionNodeQuaternionPosToolCoord(void *, void *, void *, int, int);
extern void iosApplyRotMatrix(void *, void *, void *);
extern int ClipCollisionFinder(void *, void *, void *, void *);
extern int ClipCollisionDirectCallBackOneObj(void *, void *, void *, int, int, int, int, int);
extern void GetQuaternionByAxisDirZX(void *, void *, void *);
extern void DivQuaternion(void *, void *, void *);
extern void GetEulerXYZFromQuaternion(void *, void *);
extern float adjustAngleForLimit(float, float);
extern void GetQuaternionByEulerXYZ(void *, float, float, float);
extern float iosGetACosfExact(float);
extern float adjustAnglePI(float);
extern void SetQuaternionByAxisRotateV(void *, short, void *);
extern int GetLimitationQuaternion(void *, void *, float);
extern void FlushCollisionWork(void *);
extern void scrRun(void);

static const F4 RO_0017F900 = { 0.0f, 0.0f, -1.0f, 1.0f };

static inline void normalize3(void *v)
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

static inline void normalize4(void *v)
{
    __asm__ __volatile__("lqc2 vf14, 0x0(%0)\n"
                         "vmul.xyzw vf15, vf14, vf14\n"
                         "vaddy.x vf15, vf15, vf15y\n"
                         "vaddz.x vf15, vf15, vf15z\n"
                         "vaddw.x vf15, vf15, vf15w\n"
                         "vrsqrt Q, vf0w, vf15x\n"
                         "vwaitq\n"
                         "vmulq.xyzw vf15, vf14, Q\n"
                         "sqc2 vf15, 0x0(%0)\n"
                         : : "r"(v) : "memory");
}

static inline void matInverse(float *dst, float *src)
{
    __asm__ __volatile__("lqc2 vf24, 0x30(%1)\n"
                         "vsubw.x vf25, vf0, vf0w\n"
                         "vmulx.xyz vf28, vf24, vf25x\n"
                         "vsub.w vf28, vf28, vf28\n"
                         "lq $8, 0x0(%1)\n"
                         "lq $9, 0x10(%1)\n"
                         "lq $10, 0x20(%1)\n"
                         "qmfc2.ni $11, vf0\n"
                         "pextlw $12, $9, $8\n"
                         "pextuw $13, $9, $8\n"
                         "pextlw $14, $11, $10\n"
                         "pextuw $15, $11, $10\n"
                         "pcpyld $8, $14, $12\n"
                         "pcpyud $9, $12, $14\n"
                         "pcpyld $10, $15, $13\n"
                         "pcpyud $11, $13, $15\n"
                         "qmtc2.ni $8, vf24\n"
                         "qmtc2.ni $9, vf25\n"
                         "qmtc2.ni $10, vf26\n"
                         "vmulax.xyzw ACC, vf24, vf28x\n"
                         "vmadday.xyzw ACC, vf25, vf28y\n"
                         "vmaddaz.xyzw ACC, vf26, vf28z\n"
                         "vmaddw.xyzw vf29, vf0, vf28w\n"
                         "vsub.w vf29, vf29, vf29\n"
                         "vadd.w vf29, vf29, vf0\n"
                         "sqc2 vf24, 0x0(%0)\n"
                         "sqc2 vf25, 0x10(%0)\n"
                         "sqc2 vf26, 0x20(%0)\n"
                         "sqc2 vf29, 0x30(%0)\n"
                         : : "r"(dst), "r"(src) : "$8", "$9", "$10", "$11", "$12", "$13", "$14", "$15", "memory");
}

static inline void scale3(void *d, void *a, float s)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "qmtc2.ni %2, vf6\n"
                         "vmulx.xyz vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(d), "r"(a), "r"(s) : "memory");
}

static inline void vadd(void *d, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vadd.xyzw vf7, vf5, vf6\n"
                         "sqc2 vf7, 0x0(%0)\n"
                         : : "r"(d), "r"(a), "r"(b) : "memory");
}

static inline void vadd3(void *d, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vadd.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(d), "r"(a), "r"(b) : "memory");
}

static inline void vsub(void *d, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "sqc2 vf7, 0x0(%0)\n"
                         : : "r"(d), "r"(a), "r"(b) : "memory");
}

static inline void matVec(void *d, void *m, void *v)
{
    __asm__ __volatile__("lqc2 vf8, 0x0(%2)\n"
                         "lqc2 vf14, 0x0(%1)\n"
                         "lqc2 vf15, 0x10(%1)\n"
                         "lqc2 vf16, 0x20(%1)\n"
                         "lqc2 vf17, 0x30(%1)\n"
                         "vmulax.xyzw ACC, vf14, vf8x\n"
                         "vmadday.xyzw ACC, vf15, vf8y\n"
                         "vmaddaz.xyzw ACC, vf16, vf8z\n"
                         "vmaddw.xyzw vf10, vf17, vf8w\n"
                         "sqc2 vf10, 0x0(%0)\n"
                         : : "r"(d), "r"(m), "r"(v) : "memory");
}

static inline float dot4(Vec *a, Vec *b)
{
    float r;
    __asm__ __volatile__("lqc2 vf14, 0x0(%1)\n"
                         "lqc2 vf15, 0x0(%2)\n"
                         "vmul.xyzw vf15, vf14, vf15\n"
                         "vaddy.x vf15, vf15, vf15y\n"
                         "vaddz.x vf15, vf15, vf15z\n"
                         "vaddw.x vf15, vf15, vf15w\n"
                         "qmfc2.ni %0, vf15\n"
                         : "=r"(r) : "r"(a), "r"(b));
    return r;
}

static inline void negate4(Vec *v)
{
    float m = -1.0f;
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                         "qmtc2.ni %1, vf6\n"
                         "vmulx.xyzw vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(v), "r"(m) : "memory");
}

static inline void lerp4(Vec *out, Vec *a, Vec *b, float t)
{
    __asm__ __volatile__("mfc1 $8, %3\n"
                         "qmtc2.ni $8, vf7\n"
                         "lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsubx.w vf8, vf0, vf7x\n"
                         "vmulax.xyzw ACC, vf5, vf7x\n"
                         "vmaddw.xyzw vf9, vf6, vf8w\n"
                         "sqc2 vf9, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b), "f"(t) : "$8", "memory");
}

static inline void vsub3(void *d, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(d), "r"(a), "r"(b) : "memory");
}

static inline void scale4(void *d, void *a, float s)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "qmtc2.ni %2, vf6\n"
                         "vmulx.xyzw vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(d), "r"(a), "r"(s) : "memory");
}

static inline void vzero(void *d)
{
    __asm__ __volatile__("sqc2 vf0, 0x0(%0)\n" : : "r"(d) : "memory");
}

static inline void quatDirZ(void *d, void *q)
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
                         : : "r"(d), "r"(q) : "memory");
}

static inline void quatDirY(void *d, void *q)
{
    __asm__ __volatile__("lqc2 vf4, 0x0(%1)\n"
                         "vmul.xyzw vf5, vf4, vf4\n"
                         "vmr32.xyzw vf6, vf4\n"
                         "vmul.xyzw vf7, vf6, vf4\n"
                         "vaddy.z vf6, vf0, vf7y\n"
                         "vsubw.z vf6, vf6, vf7w\n"
                         "vsubx.y vf6, vf0, vf5x\n"
                         "vsubz.y vf6, vf6, vf5z\n"
                         "vaddz.x vf6, vf7, vf7z\n"
                         "vsub.w vf6, vf0, vf0\n"
                         "vadd.w vf5, vf0, vf0\n"
                         "vmulw.xyz vf6, vf6, vf5w\n"
                         "vaddw.y vf6, vf6, vf0w\n"
                         "sqc2 vf6, 0x0(%0)\n"
                         : : "r"(d), "r"(q) : "memory");
}

static inline void quatDirX(void *d, void *q)
{
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
                         : : "r"(d), "r"(q) : "memory");
}

static inline float vdist(void *a, void *b)
{
    float r;
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "vmul.xyz vf7, vf7, vf7\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         ".word 0x4BA703BD\n"
                         "vwaitq\n"
                         "cfc2.ni $2, $vi22\n"
                         "mtc1 $2, %0\n"
                         : "=f"(r) : "r"(a), "r"(b) : "$2", "memory");
    return r;
}

static inline void quatToMatrix(void *out, void *quat, void *pos)
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
                         "lqc2 vf4, 0x0(%2)\n"
                         "vmove.w vf4, vf0\n"
                         "sqc2 vf4, 0x30(%0)\n"
                         : : "r"(out), "r"(quat), "r"(pos) : "memory");
}

static inline void quatMul(void *d, void *a, void *b)
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
                         : : "r"(d), "r"(a), "r"(b) : "memory");
}

#define POS (*(Vec **)(lay + 0x134))
#define QUAT (*(Vec **)(lay + 0x13C))
#define GV(o) (*(float *)(gcGlobalVar + (o)))

static inline void sheathPos(Vec *out, Vec *pos, Vec *quat, Vec *tmp)
{
    quatDirZ(tmp, quat);
    scale3(tmp, tmp, 0.6f);
    vsub(out, pos, tmp);
}

void nico_sheathScript(void)
{
    struct {
        Vec prev;          /* 0x0 */
        Vec vel;           /* 0x10 */
        Vec prevQuat;      /* 0x20 */
        Vec off;           /* 0x30 */
        Vec tgt;           /* 0x40 */
        Vec inv[4];        /* 0x50 */
        Vec m[4];          /* 0x90 */
        Vec loc;           /* 0xD0 */
        Vec col[4];        /* 0xE0 */
        Vec hitPos;        /* 0x120 */
        Vec a130;
        Vec a140;
        Vec a150;
        F4 dir;            /* 0x160 */
        Vec motPos;        /* 0x170 */
        Vec motQuat;       /* 0x180 */
        Vec a190;
        Vec a1A0;
        Vec a1B0;
        Vec a1C0;
        Vec a1D0;
        Vec a1E0;
        Vec a1F0;          /* also the callback hit result */
        Vec a200;
        Vec a210;
        Vec a220;
        union {
            Vec m2[4];     /* 0x230 */
            struct { Vec a230, a240, a250, a260; } t;
        } u;
        Vec inv2[4];       /* 0x270 */
        Vec a2B0;
    } L;
    void *obj;
    char *lay;
    void *parent;
    char *chr;
    char *a;
    register int horse asm("$19");
    int hit;
    float blend;
    float dsign;
    char *pl;
    float ang;
    char *g;
    Vec *tp;
    Vec *dp;

    obj = isysGetThisSubThread();
    lay = GetLayoutClass(obj);
    blend = 0.0f;
    horse = 0;
    sheathPos(&L.prev, POS, QUAT, &L.off);
    L.prev.v.w = 1.0f;
    L.prevQuat.q = QUAT->q;
    vzero(&L.vel);
    tp = &L.tgt;
    dp = &L.a1D0;
    for (;;) {
        hit = 0;
        parent = GetLayoutParentObj(GetLayoutClass(obj));
        a = (char *)GetAnimationClass(parent);
        chr = GetCharacterClass(parent);
        UpdateLayoutClassParentGeometry(lay, 0, 0);
        UpdateLayoutClassPastSimpleGeometry(lay);
        a = *(char **)a;
        if (a != 0 && ((*(unsigned int *)(a + 0x68) >> 3) & 1)) {
            horse = nico_GetPlayerCharacterRidingHorseObject(parent);
            quatToMatrix(L.m, QUAT, POS);
            matInverse((float *)L.inv, (float *)L.m);
            matVec(&L.loc, L.inv, &L.prev);
            L.dir = RO_0017F900;
            if (horse != 0) {
                GetMotionNodeQuaternionPos(&L.motQuat, &L.motPos, parent, SkelFocusDef_PLAYER_SHEATH3->x8, 1);
                quatDirZ(&L.dir, &L.motQuat);
                vadd(&L.a190, &L.dir, POS);
                iosApplyRotMatrix(&L.dir, L.inv, &L.dir);
            }
            scale3(&L.a130, &L.loc, -1.0f);
            scale3(&L.a130, &L.a130, 1.96f);
            scale3(&L.a140, &L.dir, 1.96f);
            vadd3(&L.a150, &L.a130, &L.a140);
            iosApplyRotMatrix(&L.a150, L.m, &L.a150);
            scale3(&L.a1A0, &L.vel, 0.85f);
            vadd3(&L.a150, &L.a150, &L.a1A0);
            scale3(&L.a150, &L.a150, GV(0x190));
            vadd3(tp, &L.a150, &L.prev);
            vsub(&L.a1B0, tp, POS);
            normalize3(&L.a1B0);
            scale3(&L.a1C0, &L.a1B0, 0.6f);
            vadd3(&L.a1C0, &L.a1C0, POS);
            L.a1C0.v.w = 1.0f;
            if (horse == 0) {
                char *col;
                quatDirY(&L.a1E0, *(Vec **)(GetLayoutClass(parent) + 0x13C));
                scale3(dp, &L.a1E0, 0.6f);
                vadd(dp, dp, &L.a1C0);
                col = chr + 0xE20;
                dp->v.w = 1.0f;
                if (ClipCollisionFinder(L.col, dp, &L.a1C0, col)) {
                    quatDirY(&L.a1F0, *(Vec **)(GetLayoutClass(obj) + 0x13C));
                    scale3(&L.a1F0, &L.a1F0, -vdist(&L.a1C0, &L.hitPos));
                    vadd3(tp, tp, &L.a1F0);
                    hit = 1;
                    vsub(&L.a1B0, tp, POS);
                    normalize3(&L.a1B0);
                    scale3(dp, &L.a1B0, 0.6f);
                    vadd3(dp, dp, POS);
                    dp->v.w = 1.0f;
                    if (ClipCollisionFinder(L.col, dp, &L.a1C0, col))
                        tp->q = L.hitPos.q;
                } else if (ClipCollisionFinder(L.col, POS, &L.prev, col)) {
                    hit = 1;
                    tp->q = L.prev.q;
                }
                vsub(&L.a200, tp, POS);
                normalize3(&L.a200);
                scale3(&L.a200, &L.a200, 0.4f);
                vadd3(tp, &L.a200, POS);
                tp->v.w = 1.0f;
                pl = GetLayoutClass(parent);
                GetMotionNodeQuaternionPos(&L.a220, &L.a210, parent, SkelFocusDef_PLAYER_SUNE_L->x8, 1);
                quatToMatrix(L.u.m2, *(Vec **)(pl + 0x13C), *(Vec **)(pl + 0x134));
                matInverse((float *)L.inv2, (float *)L.u.m2);
                matVec(&L.a210, L.inv2, &L.a210);
                tp = &L.tgt;
                matVec(&L.a2B0, L.inv2, tp);
                L.a210.v.x -= 0.05f;
                if (L.a210.v.x < L.a2B0.v.x) {
                    L.a2B0.v.x = L.a210.v.x;
                    matVec(tp, L.u.m2, &L.a2B0);
                }
            } else {
                quatDirX(&L.u.t.a250, *(Vec **)(GetLayoutClass(parent) + 0x13C));
                scale3(&L.u.t.a240, &L.u.t.a250, -0.6f);
                vadd(&L.u.t.a240, &L.u.t.a240, &L.a1C0);
                L.u.t.a240.v.w = 1.0f;
                if (ClipCollisionDirectCallBackOneObj(&L.a1F0, &L.u.t.a240, &L.a1C0, horse, 0, 0, 0, 0))
                    tp->q = L.u.t.a230.q;
            }
            vsub(dp, POS, tp);
            dp->v.w = 1.0f;
            normalize3(dp);
            quatDirX(&L.a1E0, QUAT);
            GetQuaternionByAxisDirZX(&L.a1F0, dp, &L.a1E0);
            DivQuaternion(&L.a1F0, &L.a1F0, QUAT);
            normalize4(&L.a1F0);
            GetEulerXYZFromQuaternion(&L.a200, &L.a1F0);
            L.a200.v.x = adjustAngleForLimit(L.a200.v.x, 1.7453293f);
            if (L.a200.v.y < -0.34906587f)
                L.a200.v.y = -0.34906587f;
            else if (0.17453292f < L.a200.v.y)
                L.a200.v.y = 0.17453292f;
            GetQuaternionByEulerXYZ(&L.a1F0, L.a200.v.x, L.a200.v.y, 0.0f);
            quatMul(QUAT, QUAT, &L.a1F0);
            normalize4(QUAT);
            DivQuaternion(&L.a210, QUAT, &L.prevQuat);
            normalize4(&L.a210);
            ang = adjustAnglePI(iosGetACosfExact(L.a210.v.w) * 2.0f);
            SetQuaternionByAxisRotateV(&L.a210, (int)(ang * 32768.0f / 3.1415925f), &L.a210);
            if (GetLimitationQuaternion(&L.a210, &L.a210, GV(0x190) * 12.56637f)) {
                quatMul(QUAT, &L.prevQuat, &L.a210);
                normalize4(QUAT);
            }
            horse = 1;
        } else {
            GetMotionNodeQuaternionPosToolCoord(&L.u.t.a230, &L.a220, parent, SkelFocusDef_PLAYER_SHEATH->x8, 1);
            if (horse)
                blend = 1.0f;
            if (0.0f < blend) {
                blend -= GV(0x190) + GV(0x190);
                if (!(0.0f <= blend))
                    blend = 0.0f;
            }
            if (0.0f < blend) {
                L.u.t.a240.q = L.u.t.a230.q;
                dsign = dot4(&L.prevQuat, &L.u.t.a240);
                __asm__("" : "+m"(dsign));
                if (*(int *)&dsign < 0)
                    scale4(&L.u.t.a240, &L.u.t.a240, -1.0f);
                lerp4(QUAT, &L.prevQuat, &L.u.t.a240, blend);
                normalize4(QUAT);
            } else {
                QUAT->q = L.u.t.a230.q;
            }
            horse = 0;
            POS->q = L.a220.q;
        }
        sheathPos(&L.u.t.a240, POS, QUAT, &L.u.t.a250);
        L.u.t.a240.v.w = 1.0f;
        if (!hit) {
            vsub3(&L.vel, &L.u.t.a240, &L.prev);
            scale3(&L.vel, &L.vel, GV(0x194));
        } else {
            vzero(&L.vel);
        }
        L.prev.q = L.u.t.a240.q;
        L.prevQuat.q = QUAT->q;
        UpdateLayoutClassSimpleGeometry(lay, GV(0x184));
        FlushCollisionWork(obj);
        scrRun();
        g = gcGlobalVar;
        __asm__ __volatile__("" : "+r"(g));
        if (*(float *)(g + 0x180) == 0.0f) {
            do
                scrRun();
            while (*(float *)(g + 0x180) == 0.0f);
        }
    }
}
#endif
