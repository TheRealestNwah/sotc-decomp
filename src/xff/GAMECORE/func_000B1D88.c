/* Parked draft: main script loop of a creature on the stage. Each frame it resets the script
   control, checks the stage area still exists (else marks itself not-in-area), and on returning to
   the area rotates the saved offset by the layout orientation, probes collision and either
   re-parents to the hit or starts SCRFall; while the global time scale is positive it runs the
   per-frame helpers (func_000B1128, 000AEAD0, 000AFCE8, 000B1378, 000B1BC8) and sets the
   character's float-frame flag. Never returns (loops on scrRunM). Continues in func_000B1FA8.
   Written from the m2c draft; not yet compared closely. */
#ifdef NONMATCHING
typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;

extern char gcGlobalVar[];
extern struct { char pad[4]; int ctrl; } *ScriptCtrlDef_SCRFall;
extern int AI_OptFloatFrameSample(int, int);
extern void CharaCtrlResetAllScriptCtrlStatus(int);
extern void CharaCtrlSetScriptCtrlStatus(int, int);
extern int ClipCollisionDirectCallBack(void *, Vec4 *, Vec4 *, void *, int (*)(), int, int, int (*)(), void *);
extern int AI_JudgeNotCharaObjFunc();
extern int AI_JudgeColAttrFunc();
extern Vec4 YUnitVectorInv;
extern char *GetCharacterClass(int);
extern char *GetLayoutClass(int);
extern void ParentLayoutObj(int, void *);
extern void SCRCharaTurnDirectInput(int, float);
extern void SCRSetRootScaleRatio(int, float);
extern int StageManagerCheckAreaExist(int);
extern void func_000AEAD0(int);
extern void func_000AFCE8(int);
extern void func_000B1128(int);
extern void func_000B1378(int);
extern void func_000B1BC8(int);
extern int isysGetThisSubThread(void);
extern void scrRunM(int);

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

static inline void addXYZ(Vec4 *out, Vec4 *a, Vec4 *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vadd.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static void func_000B1D88(int self)
{
    Vec4 hit[5];
    Vec4 offset __attribute__((aligned(16)));
    Vec4 end __attribute__((aligned(16)));
    Vec4 from __attribute__((aligned(16)));
    int inArea = 1;
    int thread = isysGetThisSubThread();
    int frameArg = self + 0x14;

    for (;;) {
        char *layout = GetLayoutClass(thread);
        int t = isysGetThisSubThread();

        CharaCtrlResetAllScriptCtrlStatus(t);
        SCRCharaTurnDirectInput(t, 0.0f);
        SCRSetRootScaleRatio(t, 1.0f);
        if (StageManagerCheckAreaExist(*(int *)(layout + 0x134)) != 0) {
            if (inArea == 0) {
                int t2 = isysGetThisSubThread();
                char *l2 = GetLayoutClass(t2);

                rotateByQuat(&offset, *(Vec4 **)(l2 + 0x13C), &YUnitVectorInv);
                from.q = **(s128 **)(l2 + 0x134);
                addXYZ(&end, &from, &offset);
                if (ClipCollisionDirectCallBack(hit, &from, &end, gcGlobalVar + 0x230, AI_JudgeNotCharaObjFunc, 0, 0, AI_JudgeColAttrFunc, 0) != 0)
                    ParentLayoutObj(t2, hit);
                else
                    CharaCtrlSetScriptCtrlStatus(t2, ScriptCtrlDef_SCRFall->ctrl);
            }
            inArea = 1;
            if (*(float *)(gcGlobalVar + 0x190) > 0.0f) {
                int t3;
                char *cc;

                func_000B1128(self);
                func_000AEAD0(self);
                func_000AFCE8(self);
                func_000B1378(self);
                t3 = isysGetThisSubThread();
                cc = GetCharacterClass(t3);
                if (AI_OptFloatFrameSample(t3, frameArg) != 0)
                    *(int *)(cc + 0x52C) = 1;
                else
                    *(int *)(cc + 0x52C) = 0;
                func_000B1BC8(self);
                inArea = 1;
            }
        } else {
            inArea = 0;
        }
        isysGetThisSubThread();
        scrRunM(1);
    }
}
#endif
