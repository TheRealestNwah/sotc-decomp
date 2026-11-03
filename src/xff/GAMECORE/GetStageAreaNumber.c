typedef struct {
    char name[4];
    const float *position;
    char pad8[0x18];
    int area;
    int part;
    char pad28[0x18];
} StageContext;

typedef struct {
    char pad0[0x340];
    float position[4];
} GcGlobal;

extern GcGlobal gcGlobalVar;
extern void *D_0017A868;
extern void *D_0017A86C;
extern int GetStageContext(StageContext *);

int GetStageAreaNumber(void)
{
    StageContext context;
    int n;

    context.position = gcGlobalVar.position;
    GetStageContext(&context);
    if (D_0017A868 == 0 || D_0017A86C == 0) {
        n = -1;
    } else {
        n = context.area;
    }
    return n;
}
