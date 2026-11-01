typedef int s128 __attribute__((mode(TI)));
extern void PredictMotionGeometryPotentialWithScaleElem(void *, float *, int, int, float, float);

static void func_0010FB98(char *o, float *r, float f)
{
    struct {
        float out;
        s128 v;
    } t;
    char *c = *(char **)(o + 0xCC);
    char *m = *(char **)(o + 0x1C);

    PredictMotionGeometryPotentialWithScaleElem(&t.v, &t.out, *(int *)(o + 8), *(int *)m, *(float *)(m + 0xC), -1.0f);
    if ((0.0f <= t.out && 0.0f <= *r) || (t.out <= 0.0f && *r <= 0.0f)) {
        *(float *)(o + 0x160) = *(float *)(o + 0x154) / f;
    } else {
        *(float *)(o + 0x160) = *(float *)(c + 0x58);
    }
}
