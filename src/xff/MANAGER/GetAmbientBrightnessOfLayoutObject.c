typedef struct {
    char pad0[0xC];
    int ambient;
    char pad10[0x250];
    long flags;
} LayoutObj;

typedef struct {
    char pad0[0x144];
    LayoutObj *obj;
} LayoutClass;

extern LayoutClass *GetLayoutClass(void *);
extern float iosCalcFColorToBrightness(int);

float GetAmbientBrightnessOfLayoutObject(void *layout)
{
    LayoutObj *obj = GetLayoutClass(layout)->obj;

    if (!(obj->flags & 0x10)) {
        if (obj->flags & 2) {
            return iosCalcFColorToBrightness(obj->ambient + 0x80);
        }
    }
    return 0.0f;
}
