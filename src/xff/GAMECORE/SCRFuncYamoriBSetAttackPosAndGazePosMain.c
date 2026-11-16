typedef struct {
    float x, y, z, w;
} __attribute__((aligned(16))) Vec4;

extern int DldSysUndefSymbol;
extern int ControlMode_YAMORI2_ATTACK;
extern char gcGlobalVar[];
extern char *getSCRDataCtrlWork(void *);
extern char *GetSCRCharaAIWorkPtr(void);
extern char *GetCharacterClass(void *);
extern char *GetLayoutClass(void *);
extern void func_000D1A80(void *, Vec4 *, int, int);
extern int ClipCollisionDirectCallBack(void *, void *, void *, void *, int, int, int, void *, int);
extern int arrowFilter(void *);
extern void setPosGazeCtrlWork(void *, void *);
extern void CharaCtrlSetScriptCtrlStatus(void *, int);

static const Vec4 RO_00180DD0 = { -965.0f, -69.5f, 950.0f, 1.0f };

static inline char *dldResolve(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;

    return (t != 0 && t != (int *)DldSysUndefSymbol) ? (char *)t[4] + ((v >> 18) & 0xFFF) * ((int *)t[2])[3] : 0;
}

void SCRFuncYamoriBSetAttackPosAndGazePosMain(void *obj, int a1, int a2, float f22, float f20, float f21, int u1, int u2, int u3, int u4, int u5, unsigned int *key)
{
    struct {
        Vec4 center;
        Vec4 pos;
        char hit[0x50];
        Vec4 dir;
    } L;
    char *ai;
    char *data;
    char *chr;
    char *r;
    float f1;
    int bits;

    ai = GetSCRCharaAIWorkPtr();
    data = getSCRDataCtrlWork(obj);
    chr = GetCharacterClass(obj);
    L.center = RO_00180DD0;
    func_000D1A80(obj, &L.pos, a1, a2);
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)
"
                         "lqc2 vf6, 0x0(%2)
"
                         "vsub.xyzw vf7, vf5, vf6
"
                         "sqc2 vf7, 0x0(%0)
"
                         :
                         : "r"(&L.dir), "r"(&L.center), "r"(*(char **)(*(char **)(data + 0x407C) + 0x134))
                         : "memory");
    L.dir.y = 0.0f;
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
                         :
                         : "r"(&L.dir)
                         : "memory");
    __asm__("mfc1 %0, %1" : "=r"(bits) : "f"(f20));
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)
"
                         "qmtc2.ni %1, vf6
"
                         "vmulx.xyz vf5, vf5, vf6x
"
                         "sqc2 vf5, 0x0(%0)
"
                         :
                         : "r"(&L.dir), "r"(bits)
                         : "memory");
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)
"
                         "lqc2 vf6, 0x0(%1)
"
                         "vadd.xyz vf5, vf5, vf6
"
                         "sqc2 vf5, 0x0(%0)
"
                         :
                         : "r"(&L.dir), "r"(*(char **)(*(char **)(data + 0x407C) + 0x134))
                         : "memory");
    L.dir.y += f21;
    L.dir.w = 1.0f;
    if (ClipCollisionDirectCallBack(L.hit, *(char **)(GetLayoutClass(obj) + 0x134), &L.dir, gcGlobalVar + 0x230, 0, 0, 0, arrowFilter, 0) != 0) {
        setPosGazeCtrlWork(data + 0x3CC0, &L.pos);
        *(int *)(ai + 0x41D4) = 0;
    } else {
        setPosGazeCtrlWork(data + 0x3CC0, &L.dir);
        *(int *)(ai + 0x41D4) = 1;
    }
    if (*(int *)(data + 0x3D10) != 0) {
        f1 = *(float *)(ai + 0x41C0);
        if (f1 <= 0.0f) {
            r = dldResolve(key);
            if (r != 0)
                CharaCtrlSetScriptCtrlStatus(obj, *(int *)(r + 4));
            *(float *)(ai + 0x41C0) = f22;
            f1 = f22;
        }
        *(float *)(ai + 0x41C0) = f1 - *(float *)(gcGlobalVar + 0x180);
    } else if (ControlMode_YAMORI2_ATTACK != *(int *)(chr + 0x750)) {
        *(int *)(ai + 0x41C0) = 0;
    }
}
