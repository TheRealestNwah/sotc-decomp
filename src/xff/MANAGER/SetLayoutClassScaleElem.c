typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vector;
typedef struct {
    char pad[0x90];
    Vector scale;
    Vector inverse;
} LayoutScale;
extern s128 ZeroPoint;
extern void iosGetScaleInverseVector(void *, void *);

void SetLayoutClassScaleElem(LayoutScale *layout, Vector *scale, int inverse)
{
    float maximum;
    layout->scale.q = scale->q;
    maximum = layout->scale.f[1] < layout->scale.f[0]
        ? (layout->scale.f[2] < layout->scale.f[0]
            ? layout->scale.f[0] : layout->scale.f[2])
        : (layout->scale.f[2] < layout->scale.f[1]
            ? layout->scale.f[1] : layout->scale.f[2]);
    layout->scale.f[3] = maximum;
    if (inverse)
        iosGetScaleInverseVector(&layout->inverse, &layout->scale);
    else
        layout->inverse.q = ZeroPoint;
}
