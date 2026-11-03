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
extern int GetStageContext(StageContext *);
extern char *strcpy(char *, const char *);

void GetStageName(char *name)
{
    StageContext context;

    context.position = gcGlobalVar.position;
    GetStageContext(&context);
    strcpy(name, context.name);
}
