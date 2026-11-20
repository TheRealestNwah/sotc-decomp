typedef struct {
    float angle;
    float f04;
    float f08;
    float f0C;
    float f10;
    char pad14[0x1C - 0x14];
    float f1C;
    float f20;
    char pad24[0x30 - 0x24];
} MoveParam;

typedef struct {
    int pad0;
    int status;
} ScriptCtrlDef;

#define I(p, o) (*(int *)((char *)(p) + (o)))
#define F(p, o) (*(float *)((char *)(p) + (o)))
#define P(p, o) (*(char **)((char *)(p) + (o)))
typedef union {
    float f;
    int i;
} FloatOrInt;
#define IU(p, o) (((FloatOrInt *)((char *)(p) + (o)))->i)

extern void *isysGetThisSubThread(void);
extern void func_000A33F8(char *, char *, char *, MoveParam *, char *);
extern void func_000A4858(char *, char *);
extern void func_000A3FA8(char *);
extern float func_000A3AA0(char *, float);
extern void func_000A4D58(char *, char *);
extern void func_000A4370(char *, char *);
extern void func_000A5260(char *, char *);
extern void func_000A5660(char *, char *);
extern void func_000A5900(char *, char *);
extern void SCRSetCharaMotionPlaySpeedRatioDirect(void *, float);
extern void CharaCtrlSetOutsideScriptCtrlStatus(int, int);
extern void CharaCtrlSetScriptCtrlStatus(void *, int);
extern ScriptCtrlDef *ScriptCtrlDef_SCRPlayerAnimalLandHit;
extern ScriptCtrlDef *ScriptCtrlDef_SCRJump;
extern ScriptCtrlDef *ScriptCtrlDef_SCRFlapWing;
extern ScriptCtrlDef *ScriptCtrlDef_SCRFly;
extern ScriptCtrlDef *ScriptCtrlDef_SCRGlide;
extern ScriptCtrlDef *ScriptCtrlDef_SCRStop;
extern ScriptCtrlDef *ScriptCtrlDef_SCRDeath;

/* Parked: 1 word differs (gcc emits beql for the I580 test in case 4, the
   Original beqz).
   The flag at 0x40 is read through a union so gcc may not move it past the
   float stores (strict aliasing), as in the Original. */
#ifdef NONMATCHING
static void func_000A8C48(char *w)
{
    void *th = isysGetThisSubThread();
    MoveParam p;
    int v;

    switch (I(w, 0x26C)) {
    case 0:
        if (I(w, 0x27C) == 2)
            I(w, 0x284) = 0x16;
        else
            I(w, 0x284) = 0x1A;
        break;
    case 2:
        p.f0C = 2.0f;
        F(w, 0x310) = 1.0f;
        p.angle = 0.0f;
        p.f04 = 1.0f;
        p.f08 = 1.0f;
        p.f10 = 0.0f;
        if (IU(w, 0x40))
            p.f1C = F(P(w, 0x20), 0xF0);
        else
            p.f1C = 1.0f;
        p.f20 = 0.0f;
        func_000A33F8(w, w + 0x110, w + 0x1D0, &p, P(w, 0x20) + 0x30);
        F(w, 0x30C) = 1.0f;
        I(w, 0x284) = 0x17;
        break;
    case 4:
        if (I(w, 0x274) == 1)
            func_000A4858(w, w + 0x170);
        else if (I(w, 0x580))
            func_000A3FA8(w);
        else
            func_000A4858(w, w + 0x170);
        v = I(w, 0x27C);
        if (v == 6)
            I(w, 0x284) = 0x19;
        else if (v == 5)
            I(w, 0x284) = 0x19;
        else if (v == 9)
            I(w, 0x284) = 0x19;
        else
            I(w, 0x284) = 0x18;
        break;
    case 6:
        if (I(w, 0x274) == 1)
            func_000A4858(w, w + 0x170);
        else if (I(w, 0x580)) {
            F(w, 0x310) = 1.0f;
            p.f04 = F(P(w, 0x20), 0x94);
            p.f08 = F(w, 0x310) + func_000A3AA0(w, F(P(w, 0x20), 0x9C));
            p.f0C = 0.5f;
            p.f10 = F(P(w, 0x20), 0x98);
            if (IU(w, 0x40)) {
                p.angle = F(P(w, 0x20), 0x104) * 0.01745329252f;
                p.f1C = F(P(w, 0x20), 0xF0);
                p.f20 = F(P(w, 0x20), 0xEC);
            } else {
                p.angle = F(P(w, 0x20), 0x90) * 0.01745329252f;
                p.f1C = 1.0f;
                p.f20 = 0.0f;
            }
            func_000A33F8(w, w + 0x110, w + 0x1D0, &p, P(w, 0x20) + 0x50);
        } else
            func_000A4D58(w, w + 0x170);
        v = I(w, 0x27C);
        if (v == 4)
            I(w, 0x284) = 0x18;
        else if (v == 5)
            I(w, 0x284) = 0x19;
        else if (v == 9)
            I(w, 0x284) = 0x19;
        else
            I(w, 0x284) = 0x19;
        break;
    case 7:
        F(w, 0x310) = 1.0f;
        p.f04 = 1.0f;
        p.f08 = F(w, 0x310) + func_000A3AA0(w, F(P(w, 0x20), 0x9C));
        p.f0C = 2.0f;
        p.f10 = F(P(w, 0x20), 0x88);
        if (IU(w, 0x40)) {
            p.angle = F(P(w, 0x20), 0x100) * 0.01745329252f;
            p.f1C = F(P(w, 0x20), 0xF0);
            p.f20 = F(P(w, 0x20), 0xEC);
        } else {
            p.f1C = 1.0f;
            p.angle = 0.0f;
            p.f20 = 0.0f;
        }
        func_000A33F8(w, w + 0x110, w + 0x1D0, &p, P(w, 0x20) + 0x40);
        if (I(w, 0x27C) == 4)
            I(w, 0x284) = 0x18;
        break;
    case 5:
        func_000A4370(w, w + 0x170);
        v = I(w, 0x27C);
        if (v == 4)
            I(w, 0x284) = 0x18;
        else if (v == 6)
            I(w, 0x284) = 0x19;
        else if (v == 9)
            I(w, 0x284) = 0x19;
        else
            I(w, 0x284) = 0x19;
        break;
    case 9:
        func_000A5260(w, w + 0xB0);
        v = I(w, 0x27C);
        if (v == 10)
            I(w, 0x284) = 0x19;
        else if (v == 4)
            I(w, 0x284) = 0x18;
        else if (v == 14)
            I(w, 0x284) = 0x1A;
        else if (v == 15)
            I(w, 0x284) = 0x19;
        else if (v == 13)
            I(w, 0x284) = 0x18;
        else if (F(w, 0x2F4) < 0.0f ? F(w, 0x2F4) < -0.5f : 0.5f < F(w, 0x2F4))
            I(w, 0x284) = 0x18;
        else
            I(w, 0x284) = 0x19;
        break;
    case 13:
        func_000A3FA8(w);
        v = I(w, 0x27C);
        if (v == 4)
            I(w, 0x284) = 0x18;
        else if (v == 9)
            I(w, 0x284) = 0x19;
        else if (v == 14)
            I(w, 0x284) = 0x1A;
        else
            I(w, 0x284) = 0x18;
        break;
    case 14:
        func_000A5660(w, w + 0xB0);
        if (I(w, 0x27C) == 0)
            I(w, 0x284) = 0x15;
        else
            I(w, 0x284) = 0x1A;
        break;
    case 15:
        func_000A5900(w, w + 0xB0);
        if (I(w, 0x27C) == 16)
            I(w, 0x284) = 0x19;
        else
            I(w, 0x284) = 0x19;
        break;
    case 16:
        F(w, 0x310) = 1.0f;
        p.f0C = 2.0f;
        p.f04 = 1.0f;
        p.f08 = 1.0f;
        p.f10 = 1.0f;
        if (IU(w, 0x40)) {
            p.angle = 0.0f;
            p.f1C = F(P(w, 0x20), 0xF0);
            p.f20 = F(P(w, 0x20), 0xEC);
        } else {
            p.f1C = 1.0f;
            p.angle = 0.1745329252f;
            p.f20 = 0.0f;
        }
        func_000A33F8(w, w + 0x110, w + 0x1D0, &p, P(w, 0x20) + 0x40);
        if (I(w, 0x27C) == 4)
            I(w, 0x284) = 0x18;
        else
            I(w, 0x284) = 0x18;
        break;
    case 18:
        SCRSetCharaMotionPlaySpeedRatioDirect(th, 1.0f);
        I(w, 0x284) = 0x1B;
        break;
    case 19:
        CharaCtrlSetOutsideScriptCtrlStatus(I(w, 0x24), ScriptCtrlDef_SCRPlayerAnimalLandHit->status);
        SCRSetCharaMotionPlaySpeedRatioDirect(th, 1.0f);
        I(w, 0x284) = 0x1B;
        break;
    case 20:
        if (I(w, 0x27C) == 4)
            I(w, 0x284) = 0x18;
        break;
    }
    v = I(w, 0x7BC);
    if (v >= 2)
        I(w, 0x284) = 0x1B;
    if (v > 0)
        I(w, 0x7BC) = v + 1;
    switch (I(w, 0x284)) {
    case 0x15:
        break;
    case 0x16:
        CharaCtrlSetScriptCtrlStatus(th, ScriptCtrlDef_SCRJump->status);
        break;
    case 0x17:
        CharaCtrlSetScriptCtrlStatus(th, ScriptCtrlDef_SCRFlapWing->status);
        break;
    case 0x18:
        CharaCtrlSetScriptCtrlStatus(th, ScriptCtrlDef_SCRFly->status);
        break;
    case 0x19:
        CharaCtrlSetScriptCtrlStatus(th, ScriptCtrlDef_SCRGlide->status);
        break;
    case 0x1A:
        CharaCtrlSetScriptCtrlStatus(th, ScriptCtrlDef_SCRStop->status);
        break;
    case 0x1B:
        CharaCtrlSetScriptCtrlStatus(th, ScriptCtrlDef_SCRDeath->status);
        break;
    }
}
#endif
