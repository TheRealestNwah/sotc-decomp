typedef int s128 __attribute__((mode(TI)));
typedef struct { char pad0[0x190]; float dt; char pad194[0x2B0 - 0x194]; char objs[4]; } GcGlobal;
typedef struct { char pad0[0x134]; s128 *pos; char pad138[4]; s128 *rot; } LayoutClass;
typedef struct { char pad0[0x53B]; char col; } CharClass;
typedef struct { int x0; int x4; char pad8[4]; float xC; char pad10[4]; float x14; float x18; } Timer7D0;
typedef struct { char pad0[0x28]; float x28; float x2C; } Timer890;
typedef struct {
    int type; char pad4[0x10]; char frame[0x10]; int obj; char pad28[0x1C]; int x44;
    char pad48[0x48]; float x90; char pad94[0x260 - 0x94];
    int x260; int x264; int x268; int x26C; int x270; int x274; int x278; int x27C;
    char pad280[0x10]; float x290; char pad294[4]; float x298; char pad29C[4]; float x2A0;
    char pad2A4[0x1C]; float x2C0; float x2C4; float x2C8; float x2CC;
    char pad2D0[0x60]; s128 x330; char pad340[0x10]; s128 x350;
    char pad360[0x7B4 - 0x360]; float x7B4; char pad7B8[4]; int x7BC; char pad7C0[0x10];
    Timer7D0 t7D0; char pad7EC[0x890 - 0x7EC]; Timer890 t890;
} KiteWork;

extern GcGlobal gcGlobalVar;
extern int isysGetThisSubThread(void);
extern int SCRGetFirstObj(void *);
extern void scrRun(void);
extern void scrRunM(int);
extern LayoutClass *GetLayoutClass(int);
extern CharClass *GetCharacterClass(int);
extern void SetLayoutObjAccessSwitch(int, int);
extern void SetCharacterObjCollisionProcFlag(int, int);
extern void AI_OptFloatFrameSample(int, void *);
extern void func_0009EB78(KiteWork *);
extern void func_000A76F0(KiteWork *);
extern void func_000A7908(KiteWork *);
extern void func_000A8018(KiteWork *);
extern void func_000A27C8(KiteWork *);
extern void func_000A2D50(KiteWork *);
extern void func_000A2F48(KiteWork *, int);
extern void func_000A8C48(KiteWork *);
extern void func_000A92A0(KiteWork *);

static void func_000A9A10(KiteWork *w)
{
    Timer7D0 *t = &w->t7D0;
    Timer890 *u = &w->t890;
    GcGlobal *g = &gcGlobalVar;
    int th;
    int st;
    CharClass *cls;
    LayoutClass *lc;

    for (;;) {
        th = isysGetThisSubThread();
        while ((w->obj = SCRGetFirstObj(gcGlobalVar.objs)) == 0) {
            scrRun();
        }
        if (((float *)GetLayoutClass(th)->pos)[1] < -1000.0f) {
            SetLayoutObjAccessSwitch(th, 0);
            for (;;) {
                scrRunM(1);
            }
        }
        while (g->dt >= 1.0f || g->dt == 0.0f) {
            scrRunM(1);
        }
        func_0009EB78(w);
        func_000A76F0(w);
        func_000A7908(w);
        func_000A8018(w);
        func_000A27C8(w);
        func_000A2D50(w);
        func_000A2F48(w, 0);
        st = w->x26C;
        if ((st == 4 || st == 6 || st == 5) && w->x260 == 0x1C) {
            w->x26C = 0;
            w->x27C = 2;
        }
        func_000A8C48(w);
        func_000A92A0(w);
        th = isysGetThisSubThread();
        cls = GetCharacterClass(th);
        AI_OptFloatFrameSample(th, w->frame);
        st = w->type;
        if (st != 6) {
            st = w->x26C;
            if (w->x44 != 0 && st < 0x12) {
            on:
                SetCharacterObjCollisionProcFlag(th, 1);
                cls->col = 0;
            } else if (st == 0x12) {
                goto on;
            } else if (st != 0x13 && w->x7BC > 0) {
                goto on;
            } else {
                SetCharacterObjCollisionProcFlag(th, 0);
                if (w->x90 > 80.0f) {
                    cls->col = 1;
                } else {
                    cls->col = 0;
                }
            }
        }
        lc = GetLayoutClass(w->obj);
        { s128 *p = lc->pos; w->x330 = *p; }
        { s128 *p = lc->rot; w->x350 = *p; }
        isysGetThisSubThread();
        scrRunM(1);
        w->x290 += g->dt;
        w->x298 += g->dt;
        w->x2A0 += g->dt;
        w->x2C0 += g->dt;
        w->x2C4 += g->dt;
        w->x2C8 += g->dt;
        w->x2CC += g->dt;
        w->x7B4 += g->dt;
        w->x268 = w->x26C;
        w->x270 = w->x274;
        w->x278 = w->x27C;
        w->x264 = w->x260;
        t->x4 = t->x0;
        t->xC += g->dt;
        t->x14 += g->dt;
        t->x18 = 1.0f;
        u->x28 += g->dt;
        u->x2C += g->dt;
    }
}
