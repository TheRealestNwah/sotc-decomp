/* Eases the live fog state B_00147398 toward the target B_00147370 over D_00130410 frames (1/remaining step), then applies it like setFogImmediate. The float fields are int/float unions so the int field copies alias them, as in the Original. */
typedef union { int i; float f; } IF;
typedef struct {
    int flag;
    IF near;
    IF far;
    IF c;
    IF d;
    IF e;
    int f;
    int r;
    int g;
    int b;
} FogState;

extern FogState B_00147398;
extern FogState B_00147370;
extern float B_001473C0;
extern float B_001473C4;
extern float B_001473C8;
extern int D_00130410;
extern float D_00130414;
extern int D_0013041C;
extern void graphSetFogParam(int, int, int, int, float, float);
extern void iosSetBGColor(int, int, int);

void foginterp(void)
{
    int r;
    int g;
    int b;

    if (D_00130410 == 0) {
        B_00147398.flag = 1;
        B_00147398.near.f = B_00147370.near.f;
        B_00147398.far.f = B_00147370.far.f;
        B_00147398.c.f = B_00147370.c.f;
        B_00147398.d.f = B_00147370.d.f;
        B_00147398.f = B_00147370.f;
        B_00147398.r = B_00147370.r;
        B_00147398.g = B_00147370.g;
        B_00147398.b = B_00147370.b;
    } else {
        float t = 1.0f / (float)D_00130410;
        D_00130410 -= 1;
        B_00147398.near.f = B_00147398.near.f + ((B_00147370.near.f - B_00147398.near.f) * t);
        B_00147398.far.f = B_00147398.far.f + ((B_00147370.far.f - B_00147398.far.f) * t);
        B_00147398.c.f = B_00147398.c.f + ((B_00147370.c.f - B_00147398.c.f) * t);
        B_00147398.d.f = B_00147398.d.f + ((B_00147370.d.f - B_00147398.d.f) * t);
        B_00147398.f = (int)((float)B_00147398.f + ((float)(B_00147370.f - B_00147398.f) * t));
        B_00147398.r = (int)((float)B_00147398.r + ((float)(B_00147370.r - B_00147398.r) * t));
        B_00147398.g = (int)((float)B_00147398.g + ((float)(B_00147370.g - B_00147398.g) * t));
        B_00147398.b = (int)((float)B_00147398.b + ((float)(B_00147370.b - B_00147398.b) * t));
    }
    r = (int)((float)B_00147398.r * D_00130414);
    g = (int)((float)B_00147398.g * D_00130414);
    b = (int)((float)B_00147398.b * D_00130414);
    if (B_00147398.flag != 0) {
        graphSetFogParam(r, g, b, B_00147398.f, 0.0f, 510.0f);
    } else {
        float diff = B_00147398.far.f - B_00147398.near.f;
        graphSetFogParam(r, g, b, B_00147398.f,
                         (B_00147398.far.f * B_00147398.near.f * (B_00147398.c.f - B_00147398.d.f)) / diff,
                         ((((B_00147398.d.f - B_00147398.c.f) * (B_00147398.far.f + B_00147398.near.f)) / diff) + (B_00147398.d.f + B_00147398.c.f)) * B_00147398.e.f);
    }
    if (D_0013041C != 0) {
        iosSetBGColor((int)B_001473C0, (int)B_001473C4, (int)B_001473C8);
    } else {
        iosSetBGColor(r, g, b);
    }
    D_00130414 = 1.0f;
}
