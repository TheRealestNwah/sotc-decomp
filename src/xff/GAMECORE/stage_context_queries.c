typedef int s128 __attribute__((mode(TI)));

typedef struct {
    char name[4];
    const float *position;
    char pad8[0x18];
    int area;
    int part;
    char pad28[8];
    s128 center;
} StageContext;

extern int GetStageContext(StageContext *);
extern int getstagenumber(int);
extern unsigned char gcGlobalVar[];
extern int D_0017A868;
extern int D_0017A86C;

int GetStageContextByPos(StageContext *context, const float *position)
{
    context->position = position;
    GetStageContext(context);
    if (D_0017A868 != 0 && D_0017A86C != 0) {
        return context->area;
    }
    return -1;
}

int GetStageAreaNumberByPos(const float *position)
{
    StageContext context;
    context.position = position;
    GetStageContext(&context);
    if (D_0017A868 != 0 && D_0017A86C != 0) {
        return context.area;
    }
    return -1;
}

int GetStageNumberByPos(void)
{
    StageContext context;
    context.position = (const float *)(gcGlobalVar + 0x340);
    GetStageContext(&context);
    if (D_0017A868 != 0 && D_0017A86C != 0) {
        return getstagenumber(
            (getstagenumber((context.area << 5) | (context.part & 0x1F)) << 15)
            | ((context.area << 5) | (context.part & 0x1F)));
    }
    return -1;
}
