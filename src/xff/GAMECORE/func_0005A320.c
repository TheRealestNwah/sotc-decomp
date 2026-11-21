/* Horse turn input: picks a GoR/GoL script control bit from the turn angle, with a hold timer (0x41E8) before reversing direction; the work fields go through an int/float union so the 0x41E4 store keeps its place before the gcGlobalVar float load. */
#define fabsf __builtin_fabsf
extern char gcGlobalVar[];
extern char *ScriptCtrlDef_SCRGoL;
extern char *ScriptCtrlDef_SCRGoR;
extern int ControlMode_HORSE_TURN_WALK;
extern float RO_0017D4E8;
extern char *GetSCRCharaAIWorkPtr(void *);
extern char *GetCharacterClass(void *);
extern float calcProgRotRatio(float, float, float, float, float);

typedef union { long l; int i; float f; } LI;

#define W(o) (((LI *)(w + (o)))->i)
#define WF(o) (((LI *)(w + (o)))->f)
#define CTRL (((LI *)(d + 0x1C0))->l)
#define BIT(s) (1L << *(int *)((s) + 4))

static int func_0005A320(void *obj, float *in, char *d, float ang)
{
    char *w;
    char *cc;
    char *p;
    float r;
    float thr;
    char *g;
    float thr2;

    w = GetSCRCharaAIWorkPtr(obj);
    cc = GetCharacterClass(obj);
    p = *(char **)(cc + 0x1C0);
    if (!(CTRL & (BIT(ScriptCtrlDef_SCRGoR) | BIT(ScriptCtrlDef_SCRGoL)))) {
        if ((float)*(int *)(p + 0x74) != 0.0f) {
            g = gcGlobalVar;
            thr = 0.008726647f;
            r = calcProgRotRatio(ang, (float)*(int *)(p + 0x74) * 0.017453294f, *(float *)(g + 0x190),
                                 *(float *)(cc + 0x72C) * 0.017453294f, *(float *)(p + 0x78));
            if (r != 0.0f) {
                W(0x41E4) = 0;
                if (thr < ang) {
                    if (fabsf(in[2]) <= **(float **)(w + 0x41C4) && in[2] <= r) {
                        if (W(0x41E0) == 2 && WF(0x41E8) < 2.0f) {
                            W(0x41E4) = W(0x41E0);
                            WF(0x41E8) = WF(0x41E8) + *(float *)(g + 0x180);
                        } else {
                            WF(0x41E8) = 0.0f;
                            W(0x41E4) = 1;
                        }
                    }
                } else if (ang < -thr) {
                    if (fabsf(in[2]) <= **(float **)(w + 0x41C4) && -r <= in[2]) {
                        if (W(0x41E0) == 1 && WF(0x41E8) < 2.0f) {
                            W(0x41E4) = W(0x41E0);
                            WF(0x41E8) = WF(0x41E8) + *(float *)(g + 0x180);
                        } else {
                            WF(0x41E8) = 0.0f;
                            W(0x41E4) = 2;
                        }
                    }
                }
                if (W(0x41E4) == 1) {
                    CTRL |= BIT(ScriptCtrlDef_SCRGoR);
                    CTRL &= ~BIT(ScriptCtrlDef_SCRGoL);
                    in[2] = r;
                } else if (W(0x41E4) == 2) {
                    CTRL |= BIT(ScriptCtrlDef_SCRGoL);
                    CTRL &= ~BIT(ScriptCtrlDef_SCRGoR);
                    in[2] = -r;
                }
                return 1;
            }
        } else if (ControlMode_HORSE_TURN_WALK == *(int *)(cc + 0x750)) {
            W(0x41E4) = 0;
            thr2 = 0.052359876f;
            if (thr2 < ang) {
                if (fabsf(in[2]) <= **(float **)(w + 0x41C4)) {
                    if (W(0x41E0) == 2 && WF(0x41E8) < 2.0f) {
                        W(0x41E4) = W(0x41E0);
                        WF(0x41E8) = WF(0x41E8) + *(float *)(gcGlobalVar + 0x180);
                    } else {
                        WF(0x41E8) = 0.0f;
                        W(0x41E4) = 1;
                    }
                }
            } else if (ang < -thr2) {
                if (fabsf(in[2]) <= **(float **)(w + 0x41C4)) {
                    if (W(0x41E0) == 1 && WF(0x41E8) < 2.0f) {
                        W(0x41E4) = W(0x41E0);
                        WF(0x41E8) = WF(0x41E8) + *(float *)(gcGlobalVar + 0x180);
                    } else {
                        WF(0x41E8) = 0.0f;
                        W(0x41E4) = 2;
                    }
                }
            }
            if (W(0x41E4) == 1) {
                CTRL |= BIT(ScriptCtrlDef_SCRGoR);
                CTRL &= ~BIT(ScriptCtrlDef_SCRGoL);
                in[2] = 1.0f;
                return 1;
            }
            if (W(0x41E4) == 2) {
                CTRL |= BIT(ScriptCtrlDef_SCRGoL);
                CTRL &= ~BIT(ScriptCtrlDef_SCRGoR);
                in[2] = -1.0f;
                return 1;
            }
        }
    }
    WF(0x4224) = RO_0017D4E8;
    return 0;
}
