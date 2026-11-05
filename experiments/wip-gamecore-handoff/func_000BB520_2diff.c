typedef struct {
    char pad[0x190];
    float x190;
} GcGlobalVar;

extern GcGlobalVar gcGlobalVar;

extern int isysGetThisSubThread(void);
extern void scrRunM(int);
extern void CharaCtrlResetAllScriptCtrlStatus(int);
extern void SCRCharaTurnDirectInput(int, float);
extern void AI_OptFloatFrameSample(int, void *);
extern void func_000BA290(void *);
extern void func_000B7C58(void *);
extern void func_000B8510(void *);
extern void func_000B8AF8(void *, int);
extern void func_000BA980(void *);
extern void func_000BA520(void *);

typedef struct {
    char pad0[0x14];
    char x14[0x13C];
    float x150;
    float x154;
    float x158;
    float x15C;
    float x160;
    float x164;
    char pad168[0x10];
    float x178;
    float x17C;
    char pad180[4];
    float x184;
    char pad188[4];
    float x18C;
    char pad190[4];
    float x194;
    char pad198[4];
    float x19C;
} Work;

typedef union { float f; int i; } F1;
#define CP(d,s) (*(F1 *)&w->d = *(F1 *)&w->s)
void func_000BB520(Work *w)
{
    int th;

    for (;;) {
        while (gcGlobalVar.x190 >= 1.0f)
            scrRunM(1);
        th = isysGetThisSubThread();
        CharaCtrlResetAllScriptCtrlStatus(th);
        SCRCharaTurnDirectInput(th, 0.0f);
        func_000BA290(w);
        func_000B7C58(w);
        func_000B8510(w);
        func_000B8AF8(w, 0);
        func_000BA980(w);
        func_000BA520(w);
        AI_OptFloatFrameSample(isysGetThisSubThread(), w->x14);
        {
            F1 a, b, d, c;
            a = *(F1 *)&w->x15C;
            b = *(F1 *)&w->x150;
            d = *(F1 *)&w->x178;
            c = *(F1 *)&w->x164;
            *(F1 *)&w->x158 = a;
            *(F1 *)&w->x160 = c;
            *(F1 *)&w->x154 = b;
            *(F1 *)&w->x17C = d;
        }
        w->x18C += gcGlobalVar.x190;
        w->x194 += gcGlobalVar.x190;
        w->x19C += gcGlobalVar.x190;
        w->x184 += gcGlobalVar.x190;
        isysGetThisSubThread();
        scrRunM(1);
    }
}
