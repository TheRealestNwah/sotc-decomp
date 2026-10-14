typedef struct {
    char pad0[0x168];
    float fadeTime;
} GcGlobalVar;

extern GcGlobalVar gcGlobalVar;

typedef struct {
    float startTime;
    float endTime;
    float startValue;
    float endValue;
    float value;
} FadeParam;

void calcFadeParam(FadeParam *f)
{
    float time = gcGlobalVar.fadeTime;
    float endTime = f->endTime;

    if (time <= endTime) {
        float startTime = f->startTime;
        float value = f->startValue;

        time = (time - startTime) / (endTime - startTime);
        value += (f->endValue - value) * time;
        f->value = value;
    } else {
        f->value = f->endValue;
    }
}
