/* Tail-state handler for a boss part. On a state change to 3 (death) it publishes the stored
   quadword and switches the script control to SCRDeath; on 2 it detaches the layout object, resets
   the sync mode, rotates YUnitVector by the layout's orientation quaternion (VU0) and picks
   SCRTailDamage or SCRTailFallDamage by the sign of the rotated Y component. */
typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;

typedef struct {
    char pad0[4];
    int ctrl;
} ScriptCtrlDef;

extern ScriptCtrlDef *ScriptCtrlDef_SCRDeath;
extern ScriptCtrlDef *ScriptCtrlDef_SCRTailDamage;
extern ScriptCtrlDef *ScriptCtrlDef_SCRTailFallDamage;
extern void CharaCtrlSetScriptCtrlStatus(int, int);
extern void ForceUnparentLayoutObj(int);
extern int GetCharacterClass(int);
extern char *GetLayoutClass(int);
extern char *GetScriptCharacterClass(int);
extern void ResetCharacterClassSyncMode(int);
extern void SetCharacterObjCollisionProcFlag(int, int);
extern int isysGetThisSubThread(void);

typedef struct {
    char pad0[0x20];
    int owner;
    int old;
    int state;
    int flag;
    s128 value;
} PartState;

static inline void rotateByQuat(Vec4 *out, Vec4 *q, Vec4 *v)
{
    __asm__ __volatile__("lqc2 vf8, 0x0(%2)\n"
                         "vaddw.xyz vf12, vf0, vf0w\n"
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
                         "vmulax.xyzw ACC, vf14, vf8x\n"
                         "vmadday.xyzw ACC, vf15, vf8y\n"
                         "vmaddaz.xyzw ACC, vf16, vf8z\n"
                         "vmaddw.xyzw vf10, vf0, vf8w\n"
                         "sqc2 vf10, 0x0(%0)\n"
                         : : "r"(out), "r"(q), "r"(v) : "memory");
}

extern Vec4 YUnitVector;

static void func_000B48A8(PartState *p)
{
    int thread = isysGetThisSubThread();

    if (p->old != p->state) {
        switch (p->state) {
        case 2: {
            int owner = p->owner;
            int self = isysGetThisSubThread();
            int t2;
            Vec4 vel[2];

            if (owner != 0) {
                char *cc = *(char **)(GetScriptCharacterClass(owner) + 0x1200);
                if (cc != 0) {
                    char *sub = *(char **)(cc + 0x10);
                    if (sub != 0)
                        *(int *)(sub + 0xC) = 1;
                }
                ForceUnparentLayoutObj(self);
                ResetCharacterClassSyncMode(GetCharacterClass(self));
            }
            t2 = isysGetThisSubThread();
            rotateByQuat(&vel[1], *(Vec4 **)(GetLayoutClass(t2) + 0x13C), &YUnitVector);
            if (vel[1].f[1] >= 0.0f)
                CharaCtrlSetScriptCtrlStatus(t2, ScriptCtrlDef_SCRTailDamage->ctrl);
            else
                CharaCtrlSetScriptCtrlStatus(t2, ScriptCtrlDef_SCRTailFallDamage->ctrl);
            SetCharacterObjCollisionProcFlag(thread, 1);
            break;
        }
        case 3:
            if (p->flag != 0)
                **(s128 **)(GetLayoutClass(thread) + 0x134) = p->value;
            CharaCtrlSetScriptCtrlStatus(isysGetThisSubThread(), ScriptCtrlDef_SCRDeath->ctrl);
            break;
        }
    }
}
