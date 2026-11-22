extern int *DldSysUndefSymbol;
extern void setAttainRadPathWork(void *, float);
extern void func_00107130(int, char *);
extern void analyzeMotionProperty(int obj, char *elem, float *len, float *speed, float *yaw, float scale, float from);
extern void _setStopCtrlModeBaseMoveWork(char *, char *);

static inline char *dldBase(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;
    return t != 0 && t != DldSysUndefSymbol ? (char *)t[4] : 0;
}

static inline char *dldElem(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    char *t = off != 0 ? *(char **)((char *)h - off) : 0;
    return (t != 0 && t != (char *)DldSysUndefSymbol) ? *(char **)(t + 0x10) + ((v >> 18) & 0xFFF) * *(int *)(*(char **)(t + 8) + 0xC) : 0;
}

typedef union { float f; unsigned int i; } IF;
#define F(p, o) (((IF *)((char *)(p) + (o)))->f)
#define P(p, o) (*(unsigned int *)((char *)(p) + (o)))
#define H(o) ((unsigned int *)(s + (o)))
#define DEG 0.017453293f

void createFastLegCtrlWork(int obj, char *w, unsigned int *def, void *path)
{
    char *s = dldBase(def);
    char *e0 = dldElem(H(0x8));
    char *e1 = dldElem(H(0xC));
    char *a, *b;
    float sp[4];

    setAttainRadPathWork(path, 0.087266460f);
    func_00107130(obj, w);
    F(w, 0x7C) = F(e0, 0x0);
    F(w, 0x80) = F(e1, 0xC);
    F(w, 0x84) = F(e0, 0x8);
    F(w, 0x74) = F(s, 0x0) * DEG;
    F(w, 0x78) = F(s, 0x4) * DEG;
    F(w, 0x88) = F(s, 0x10);
    F(w, 0x9C) = F(s, 0x28) * DEG;
    P(w, 0xA0) = (unsigned int)dldElem(H(0x2C));
    P(w, 0xA4) = (unsigned int)dldElem(H(0x30));
    P(w, 0xAC) = (unsigned int)dldElem(H(0x34));
    P(w, 0xB0) = (unsigned int)dldElem(H(0x38));
    P(w, 0xB4) = (unsigned int)dldElem(H(0x3C));
    P(w, 0xB8) = (unsigned int)dldElem(H(0x40));
    P(w, 0xBC) = (unsigned int)dldElem(H(0x64));
    F(w, 0xC0) = F(s, 0x68);
    if (P(w, 0xAC) != 0)
        analyzeMotionProperty(obj, (char *)P(w, 0xAC), 0, 0, (float *)(w + 0xA8), 1.0f, 0.0f);
    else
        *(int *)(w + 0xA8) = 0;
    _setStopCtrlModeBaseMoveWork(w, dldElem(H(0x14)));
    P(w, 0x8C) = (unsigned int)dldElem(H(0x18));
    P(w, 0x90) = (unsigned int)dldElem(H(0x1C));
    P(w, 0x94) = (unsigned int)dldElem(H(0x24));
    P(w, 0x98) = (unsigned int)dldElem(H(0x20));
    if (dldElem(H(0x44)) != 0) {
        analyzeMotionProperty(obj, dldElem(H(0x44)), &sp[0], &sp[1], 0, 1.0f, 0.0f);
        F(w, 0xC4) = sp[0] / sp[1];
    }
    if (dldElem(H(0x48)) != 0) {
        analyzeMotionProperty(obj, dldElem(H(0x48)), &sp[2], &sp[3], 0, 1.0f, 0.0f);
        F(w, 0xC8) = sp[2] / sp[3];
    }
    F(w, 0xCC) = F(s, 0x4C);
    F(w, 0xD0) = F(s, 0x50) * DEG;
    F(w, 0xD4) = F(s, 0x54);
    F(w, 0xD8) = F(s, 0x58) * DEG;
    a = dldElem(H(0x5C));
    b = dldElem(H(0x60));
    if (a != 0)
        analyzeMotionProperty(obj, a, (float *)(w + 0xDC), 0, 0, 1.0f, 0.0f);
    else
        *(int *)(w + 0xDC) = 0;
    if (b != 0)
        analyzeMotionProperty(obj, b, (float *)(w + 0xE0), 0, 0, 1.0f, 0.0f);
    else
        *(int *)(w + 0xE0) = 0;
}
