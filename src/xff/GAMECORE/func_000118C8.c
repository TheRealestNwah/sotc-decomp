/* Caption table script thread (created by DisplayCaptionTable): while captions are enabled (D_00179FE8) it advances its clock by gcGlobalVar.dt whenever it is the topmost caption context, and once the next 0x18-byte entry's start time has passed it resolves the entry's localized text (sheetFsLanguageCode), allocates a 0x34-byte caption job (text, style, position, length, fade-in/out defaulting to 0.25) and starts T_00011498 as a script object, a child of the context's parent when there is one, with func_000121C8 as delete callback. It stops when no captions are left or running and then sets *done. */
typedef struct {
    unsigned int h;
    char pad4;
    unsigned char style;
    unsigned short pos;
    float start;
    float end;
    float fadeIn;
    float fadeOut;
} CaptionEnt;

typedef struct {
    unsigned int *table;
    int parent;
    int *done;
    int prio;
    int time;
    int hidden;
    char *next;
} CaptionCtx;

typedef struct { char pad[0x180]; float dt; } GcGlobal;

extern int *DldSysUndefSymbol;
extern int D_00179FE8;
extern int D_00179FEC;
extern char *D_00179FF4;
extern int sheetFsLanguageCode;
extern GcGlobal gcGlobalVar;
extern int rootPtn;
extern char RO_0017CA38[];
extern char *iosMallocAlign(void *, int, int);
extern void T_00011498(void *);
extern void func_000121C8(void *) __attribute__((weak));
extern int gcCreateScriptObj(void (*)(void *), void *, void *, int, int, int, char *);
extern int _gcCreateChildScriptObj(void (*)(void *), void *, void *, int, int, int, char *, int);
extern void SetScriptObjDeleteCallBackFunc(int, void (*)(void *), void *);
extern void scrRun(void);

static inline int *dldTable(unsigned int *h)
{
    unsigned int off = *h & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;

    return t;
}

static inline char *dldResolve(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;

    return (t != 0 && t != DldSysUndefSymbol) ? (char *)t[4] + ((v >> 18) & 0xFFF) * ((int *)t[2])[3] : 0;
}

static inline int dldCount(unsigned int *h)
{
    int *t = dldTable(h);

    return (t != 0 && t != DldSysUndefSymbol) ? t[3] : 0;
}

static inline int *dldData(unsigned int *h)
{
    int *t = dldTable(h);

    return (t != 0 && t != DldSysUndefSymbol) ? (int *)t[4] : 0;
}

static inline int notTop(CaptionCtx *c)
{
    char *best = 0;
    char *q = D_00179FF4;
    int max = -1;

    if (D_00179FEC != 0)
        return 1;
    for (; q != 0; q = *(char **)(q + 0x18)) {
        if (*(int *)(q + 0xC) >= max) {
            max = *(int *)(q + 0xC);
            best = q;
        }
    }
    return best != (char *)c;
}

static void func_000118C8(CaptionCtx *c)
{
    CaptionEnt *e = (CaptionEnt *)dldResolve(c->table);
    int n = dldCount(c->table);
    int count = 0;
    int parent = c->parent;
    int *done = c->done;
    float t = 0.0f;
    int *hid;
    int *d;
    int text;
    int style;
    int pos;
    float len;
    float fi;
    float fo;
    int *p;
    int time;
    int obj;
    void (*cb)(void *);
    void (*fn)(void *);
    char *nm;

    while (D_00179FE8 != 0) {
        hid = &c->hidden;
        if ((c->hidden = notTop(c)) == 0)
            t += gcGlobalVar.dt;
        if (n > 0 && e->start < t) {
            d = dldData(&e->h);
            if (d != 0) {
                text = dldData((unsigned int *)d + sheetFsLanguageCode - 1)[3];
                style = e->style;
                pos = e->pos;
                len = e->end - e->start;
                fi = e->fadeIn >= 0.0f ? e->fadeIn : 0.25f;
                fo = e->fadeOut >= 0.0f ? e->fadeOut : 0.25f;
                time = c->time;
                p = (int *)iosMallocAlign(&rootPtn, 0x34, 0x10);
                p[2] = 1;
                fn = T_00011498;
                cb = func_000121C8;
                nm = RO_0017CA38;
                p[5] = time;
                p[0] = text;
                p[3] = style;
                p[4] = pos;
                ((float *)p)[6] = len;
                ((float *)p)[7] = fi;
                ((float *)p)[8] = fo;
                p[1] = (int)hid;
                p[11] = 0;
                p[12] = (int)&count;
                p[10] = 0;
                p[9] = 0;
                count++;
                if (parent != 0)
                    obj = _gcCreateChildScriptObj(fn, p, &rootPtn, 0x1000, 0, 0xA, nm, parent);
                else
                    obj = gcCreateScriptObj(fn, p, &rootPtn, 0x1000, 0, 0xA, nm);
                if (cb != 0)
                    SetScriptObjDeleteCallBackFunc(obj, cb, p);
            }
            e++;
            n--;
        }
        if (count == 0 && n == 0)
            break;
        scrRun();
    }
    if (done != 0)
        *done = 1;
}
