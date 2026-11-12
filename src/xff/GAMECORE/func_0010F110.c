extern void CharaCtrlSetScriptCtrlStatus(int, int);
extern void SCRCharaTurnDirectInput(int, float);
extern float calcProgRotRatioForMove2(void *, float);
extern float iosGetATan2fExact(float, float);
extern char *ScriptCtrlDef_SCRGoL;
extern char *ScriptCtrlDef_SCRGoR;

static void func_0010F110(char *c, int mode, float ang)
{
    float v[4] __attribute__((aligned(16)));
    char *a = *(char **)(c + 0xCC);
    char *b = *(char **)(c + 0x14);
    float r = 0.0f;

    if (*(int *)(b + 0x750) == *(int *)(a + 0x70)) {
        if (*(int *)(a + 0x34) == 1) {
            __asm__ __volatile__("lqc2 vf8, 0x0(%1)\n"
                                 "lqc2 vf14, 0x0(%2)\n"
                                 "lqc2 vf15, 0x10(%2)\n"
                                 "lqc2 vf16, 0x20(%2)\n"
                                 "lqc2 vf17, 0x30(%2)\n"
                                 "vmulax.xyzw ACC, vf14, vf8x\n"
                                 "vmadday.xyzw ACC, vf15, vf8y\n"
                                 "vmaddaz.xyzw ACC, vf16, vf8z\n"
                                 "vmaddw.xyzw vf10, vf17, vf8w\n"
                                 "sqc2 vf10, 0x0(%0)\n"
                                 : : "r"(v), "r"(*(char **)(c + 4) + 0xB0), "r"(c + 0x20) : "memory");
            v[1] = r;
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
            ang = iosGetATan2fExact(v[0], v[2]);
        } else if (mode != 3 || *(float *)(b + 0x570) != r) {
            if (ang >= r) {
                if (ang >= 1.5707963f)
                    ang -= 1.5707963f;
                else
                    ang += -1.5707963f;
            } else if (ang <= -1.5707963f) {
                ang -= -1.5707963f;
            } else {
                ang += 1.5707963f;
            }
        }
    } else if ((unsigned)(mode - 4) < 2U) {
        if (ang >= r)
            ang += -3.1415927f;
        else
            ang += 3.1415927f;
    }
    r = calcProgRotRatioForMove2(c, ang);
    if (r != 0.0f) {
        if (ang > 0.0523598775f) {
            CharaCtrlSetScriptCtrlStatus(*(int *)(c + 8), *(int *)(ScriptCtrlDef_SCRGoR + 4));
            SCRCharaTurnDirectInput(*(int *)(c + 8), r);
            return;
        }
        if (ang < -0.0523598775f) {
            CharaCtrlSetScriptCtrlStatus(*(int *)(c + 8), *(int *)(ScriptCtrlDef_SCRGoL + 4));
            SCRCharaTurnDirectInput(*(int *)(c + 8), -r);
        }
    }
}
