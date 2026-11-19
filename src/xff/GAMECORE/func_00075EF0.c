/* Picks the nearest pickup within squared range 1.0 of the player: first over the item group (gcGlobalVar + 0x2A4), then, when none was found, over fruit-group members whose control mode is FRUIT_LAND or GEX_TAIL_DEATH (+0x2A0). The loops must be `for (; g; g = next(g)) { cur = *g; ... }` (the exit loads the last cur for isysGroupForExit); the iterator/layout pointers are pinned to s1/s0 in the first loop and s0/s1 in the second. The distance is one VU0 asm (early-clobber output, mtc1 to the float result inside the same asm so c.lt.s schedules right after it), in two copies with operands pinned to a0/v1 and v1/a0. */
typedef struct {
    char pad0[0x134];
    float *pos;
    char pad138[0x1B8 - 0x138];
    char flag;
} Layout;

typedef struct {
    char pad0[0x750];
    int mode;
} CharaClass;

typedef struct {
    char pad0[4];
    int status;
} ScriptCtrlDef;

extern char gcGlobalVar[];
extern int ControlMode_FRUIT_LAND;
extern int ControlMode_GEX_TAIL_DEATH;
extern float RO_0017E224;
extern ScriptCtrlDef *ScriptCtrlDef_SCRPlayerItemPickUp;
extern ScriptCtrlDef *ScriptCtrlDef_SCRPlayerFruitPickUp;
extern int isysGetThisSubThread(void);
extern int *isysGroupForFirst(void *, int);
extern int *isysGroupForNext(int *, int);
extern void isysGroupForExit(int, int);
extern Layout *GetLayoutClass(int);
extern CharaClass *GetCharacterClass(int);
extern void CharaCtrlSetScriptCtrlStatus(int, int);

static inline float distSq1(float *a, float *b)
{
    register float *pa_ __asm__("$4") = a;
    register float *pb_ __asm__("$3") = b;
    int bits;
    float f;

    __asm__ __volatile__("lqc2 vf5, 0x0(%2)\n"
                         "lqc2 vf6, 0x0(%3)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "vmul.xyz vf7, vf7, vf7\n"
                         "vaddy.x vf7, vf7, vf7y\n"
                         "vaddz.x vf7, vf7, vf7z\n"
                         "qmfc2.ni %0, vf7\n"
                         "mtc1 %0, %1\n"
                         : "=&r"(bits), "=f"(f)
                         : "r"(pa_), "r"(pb_)
                         : "memory");
    return f;
}

static inline float distSq2(float *a, float *b)
{
    register float *pa_ __asm__("$3") = a;
    register float *pb_ __asm__("$4") = b;
    int bits;
    float f;

    __asm__ __volatile__("lqc2 vf5, 0x0(%2)\n"
                         "lqc2 vf6, 0x0(%3)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "vmul.xyz vf7, vf7, vf7\n"
                         "vaddy.x vf7, vf7, vf7y\n"
                         "vaddz.x vf7, vf7, vf7z\n"
                         "qmfc2.ni %0, vf7\n"
                         "mtc1 %0, %1\n"
                         : "=&r"(bits), "=f"(f)
                         : "r"(pa_), "r"(pb_)
                         : "memory");
    return f;
}

static void func_00075EF0(char *o)
{
    int cur = 0;
    int best = 0;
    int self;
    float bd;
    register int *g __asm__("$17");
    register Layout *l __asm__("$16");
    float d;
    float *pa;
    float *pb;
    register int *g2 __asm__("$16");
    register Layout *l2 __asm__("$17");

    self = isysGetThisSubThread();
    bd = RO_0017E224;
    g = isysGroupForFirst(gcGlobalVar + 0x2A4, 0);
    for (; g != 0; g = isysGroupForNext(g, 0)) {
        {
            cur = *g;
            l = GetLayoutClass(cur);
            pb = GetLayoutClass(self)->pos;
            pa = l->pos;
            d = distSq1(pa, pb);
            if (d < 1.0f && d < bd) {
                bd = d;
                best = cur;
            }
        }
    }
    if (cur != 0)
        isysGroupForExit(cur, 0);
    if (best != 0) {
        *(int *)(o + 0x148) = best;
        CharaCtrlSetScriptCtrlStatus(self, ScriptCtrlDef_SCRPlayerItemPickUp->status);
        return;
    }
    cur = 0;
    g2 = isysGroupForFirst(gcGlobalVar + 0x2A0, 0);
    for (; g2 != 0; g2 = isysGroupForNext(g2, 0)) {
        {
            cur = *g2;
            l2 = GetLayoutClass(cur);
            if (l2->flag != 0 && (ControlMode_FRUIT_LAND == GetCharacterClass(cur)->mode || ControlMode_GEX_TAIL_DEATH == GetCharacterClass(cur)->mode)) {
                d = distSq2(l2->pos, GetLayoutClass(self)->pos);
                if (d < 1.0f && d < bd) {
                    bd = d;
                    best = cur;
                }
            }
        }
    }
    if (cur != 0)
        isysGroupForExit(cur, 0);
    if (best != 0) {
        *(int *)(o + 0x148) = best;
        CharaCtrlSetScriptCtrlStatus(self, ScriptCtrlDef_SCRPlayerFruitPickUp->status);
    }
}
