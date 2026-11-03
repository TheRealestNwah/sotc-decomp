typedef struct {
    char name[4];
    const float *position;
    char pad8[0x18];
    int area;
    int part;
    char pad28[0x18];
} StageContext;

extern void *D_0017A868;
extern void *D_0017A86C;
extern int GetStageContext(StageContext *);

int GetStageContextByPos(StageContext *context, const float *position)
{
    context->position = position;
    GetStageContext(context);
    if (D_0017A868 == 0 || D_0017A86C == 0) {
        return -1;
    }
    return context->area;
}
