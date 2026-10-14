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
extern char *strcpy(char *, const char *);
extern int getstagenumber(int);
extern unsigned char gcGlobalVar[];
extern int D_0017A868;
extern int D_0017A86C;

void GetStageName(char *name)
{
    StageContext context;
    context.position = (const float *)(gcGlobalVar + 0x340);
    GetStageContext(&context);
    strcpy(name, context.name);
}

int GetStageAreaNumber(void)
{
    StageContext context;
    int result;
    context.position = (const float *)(gcGlobalVar + 0x340);
    GetStageContext(&context);
    result = -1;
    if (D_0017A868 != 0 && D_0017A86C != 0) {
        result = *(volatile int *)&context.area;
    }
    return result;
}

int GetStageNumberNumber(void)
{
    StageContext context;
    int result;
    context.position = (const float *)(gcGlobalVar + 0x340);
    GetStageContext(&context);
    result = -1;
    if (D_0017A868 != 0 && D_0017A86C != 0) {
        result = getstagenumber(
            (getstagenumber((context.area << 5) | (context.part & 0x1F)) << 15)
            | ((context.area << 5) | (context.part & 0x1F)));
    }
    return result;
}
