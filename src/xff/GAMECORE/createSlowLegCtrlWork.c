extern int *DldSysUndefSymbol;
extern void func_0010FA18(int, char *, int *);
extern void analyzeMotionProperty(int, int, void *, void *, void *, float, float);
extern void _setStopCtrlModeBaseMoveWork(char *, int);

static inline char *dldResolve(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;

    return (t != 0 && t != DldSysUndefSymbol) ? (char *)t[4] + ((v >> 18) & 0xFFF) * ((int *)t[2])[3] : 0;
}

#define R(o) ((int)dldResolve((unsigned int *)(s + (o))))
typedef union { float f; unsigned int u; } U;
#define F(o) (((U *)(w + (o)))->f)
#define I(o) (*(int *)(w + (o)))
#define SF(o) (*(float *)(s + (o)))

void createSlowLegCtrlWork(int mot, char *w, unsigned int *h)
{
    unsigned int v;
    int off;
    int *t;
    char *s;

    v = *h;
    off = v & 0x3FFFF;
    t = off != 0 ? *(int **)((char *)h - off) : 0;
    s = (t != 0 && t != DldSysUndefSymbol) ? (char *)t[4] : 0;
    func_0010FA18(mot, w, t);
    analyzeMotionProperty(mot, R(8), w + 0x44, w + 0x48, 0, 1.0f, 0.0f);
    if (R(0x10) != 0) {
        analyzeMotionProperty(mot, R(0x10), w + 0x50, w + 0x54, 0, 1.0f, 0.0f);
    } else {
        I(0x50) = 0;
        I(0x54) = 0;
    }
    F(0x4C) = SF(0) * 0.0174532924f;
    F(0x58) = SF(0x18);
    F(0x38) = 1.0f;
    F(0x5C) = SF(0x1C);
    F(0x60) = SF(0x20);
    analyzeMotionProperty(mot, R(4), 0, 0, w + 0x88, 1.0f, 0.0f);
    F(0x88) = __builtin_fabsf(F(0x88));
    _setStopCtrlModeBaseMoveWork(w, R(0x24));
    I(0x64) = R(0x2C);
    I(0x6C) = R(0x28);
    I(0x70) = R(0x34);
    if (R(0xC) != 0) {
        I(0x7C) = 1;
        analyzeMotionProperty(mot, R(0xC), w + 0x80, 0, w + 0x84, 1.0f, 0.0f);
        F(0x80) = __builtin_fabsf(F(0x80));
        F(0x84) = __builtin_fabsf(F(0x84));
    } else {
        I(0x7C) = 0;
        F(0x80) = 0.0f;
        F(0x84) = 0.0f;
    }
    if (R(0x14) != 0) {
        analyzeMotionProperty(mot, R(0x14), w + 0x8C, 0, w + 0x90, 1.0f, 0.0f);
        F(0x90) = __builtin_fabsf(F(0x90));
    } else {
        I(0x8C) = 0;
        F(0x90) = 0.0f;
    }
    if (R(0x30) != 0) {
        analyzeMotionProperty(mot, R(0x30), w + 0x68, 0, 0, 1.0f, 0.0f);
    } else {
        I(0x68) = 0;
    }
    F(0xA0) = SF(0x3C);
    {
        unsigned int *hh = (unsigned int *)(s + 0x38);
        unsigned int vv = *hh;
        int oo = vv & 0x3FFFF;
        t = oo != 0 ? *(int **)((char *)hh - oo) : 0;
        I(0xA4) = (t != 0 && t != DldSysUndefSymbol) ? (int)((char *)t[4] + ((vv >> 18) & 0xFFF) * ((int *)t[2])[3]) : 0;
    }
}
