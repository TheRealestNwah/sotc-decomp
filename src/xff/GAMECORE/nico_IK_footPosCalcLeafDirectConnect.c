typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; int i[4]; } Vec4;
typedef struct {
    Vec4 pos;
    Vec4 dir;
    Vec4 target;
    int node;
    float weight;
    float time;
    int flag;
} PinAttackIK;
typedef struct {
    int object;
    char pad4[0x10];
    int node;
    unsigned int *ref;
} FootIK;

extern void *DldSysUndefSymbol;
extern int CharIkTypeDef_PINATTACKIK[];
extern s128 ZeroVector;
extern char gcGlobalVar[];
extern void GetMotionNodeQuaternionPosToolCoord(void *, void *, int, int);
extern char *GetCharacterClass(int);
extern void func_00038238(void *, int, void *, void *, void *);

#ifdef NONMATCHING /* 42 diffs, same shape as nico_IK_footPosCalc (tail call passes 1): the Original's dead t0 = 1 at entry and dead andi t1, t1, 1 before the dld lookup are not reproduced */
void nico_IK_footPosCalcLeafDirectConnect(FootIK *f)
{
    float qv[4] __attribute__((aligned(16)));
    float tmp[4] __attribute__((aligned(16)));
    int obj = f->object;
    int node;
    char *chr;
    PinAttackIK *ik;
    unsigned int *ref;
    unsigned int enc;
    int off;
    char *mod;
    char *data;
    float *tp;
    int noHit;
    register int si __asm__("$8") = 1;

    GetMotionNodeQuaternionPosToolCoord(qv, tmp, obj, f->node);
    node = f->node;
    tp = tmp;
    chr = GetCharacterClass(obj);
    ik = 0;
    if (DldSysUndefSymbol != CharIkTypeDef_PINATTACKIK &&
        *(int *)(chr + 0x1100) == *CharIkTypeDef_PINATTACKIK)
        ik = *(PinAttackIK **)(chr + 0x1110) + (node & 0xFFFEFFFF);
    noHit = 1;
    if (ik != 0) {
        float *pt = &ik->time;
        float *pw = &ik->weight;
        float t = *pt;
        if (t >= 0.0f && *pw > 0.0f) {
            t -= *(float *)(gcGlobalVar + 0x180);
            *pt = t;
            if (t > 0.0f) {
                float s = t / *pw;
                __asm__ __volatile__("mfc1 %0, %1" : "=r"(si) : "f"(s));
                __asm__ __volatile__("qmtc2.ni %2, vf7\n"
                                     "lqc2 vf5, 0x0(%0)\n"
                                     "lqc2 vf6, 0x0(%1)\n"
                                     "vsubx.w vf8, vf0, vf7x\n"
                                     "vmulax.xyz ACC, vf5, vf7x\n"
                                     "vmaddw.xyz vf5, vf6, vf8w\n"
                                     "sqc2 vf5, 0x0(%0)\n"
                                     : : "r"(&ik->pos), "r"(tp), "r"(si) : "memory");
                noHit = 0;
                ik->pos.f[3] = 1.0f;
                *(s128 *)tmp = ik->pos.q;
            }
        }
        if (noHit) {
            ik->pos.q = *(s128 *)tmp;
            ik->weight = -1.0f;
            ik->dir.q = ZeroVector;
            ik->time = -1.0f;
        }
    }
    ref = f->ref;
    enc = *ref;
    off = enc & 0x3FFFF;
    mod = off ? *(char **)((char *)ref - off) : 0;
    if (mod && mod != DldSysUndefSymbol)
        data = *(char **)(mod + 0x10) + ((enc >> 18) & 0xFFF) * *(int *)(*(char **)(mod + 8) + 0xC);
    else
        data = 0;
    func_00038238(f, 1, data, qv, tmp);
}
#endif
