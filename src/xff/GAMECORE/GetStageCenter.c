typedef int s128 __attribute__((mode(TI)));

typedef struct {
    char pad0[4];
    const float *position;
    char pad8[0x28];
    s128 center;
} StageContext;

extern int GetStageContext(StageContext *);

void GetStageCenter(s128 *center, const float *position)
{
    StageContext context;

    context.position = position;
    GetStageContext(&context);
    *center = context.center;
}
