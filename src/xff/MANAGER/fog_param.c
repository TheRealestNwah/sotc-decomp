typedef struct {
    int flag;
    float near;
    float far;
    float c;
    float d;
    float e;
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
extern float D_00130414;
extern int D_0013041C;
extern void graphSetFogParam(int, int, int, int, float, float);
extern void iosSetBGColor(int, int, int);
extern int B_001473B4;
extern int B_001473B8;
extern unsigned char B_00147374[];
extern unsigned char B_00147378[];
extern unsigned char B_0014737C[];
extern unsigned char B_00147380[];
extern unsigned char B_00147384[];
extern unsigned char B_00147388[];
extern unsigned char D_00130418[];
extern unsigned char B_0014738C[];
extern unsigned char B_00147390[];
extern unsigned char B_00147394[];

void setFogImmediate(void)
{
    int r;
    int g;
    int b;

    B_00147398 = B_00147370;
    r = (int)((float)B_00147398.r * D_00130414);
    g = (int)((float)B_00147398.g * D_00130414);
    b = (int)((float)B_00147398.b * D_00130414);
    if (B_00147398.flag != 0) {
        graphSetFogParam(r, g, b, B_00147398.f, 0.0f, 510.0f);
    } else {
        float diff = B_00147398.far - B_00147398.near;
        graphSetFogParam(r, g, b, B_00147398.f,
                         (B_00147398.far * B_00147398.near * (B_00147398.c - B_00147398.d)) / diff,
                         ((((B_00147398.d - B_00147398.c) * (B_00147398.far + B_00147398.near)) / diff) + (B_00147398.d + B_00147398.c)) * B_00147398.e);
    }
    if (D_0013041C != 0) {
        iosSetBGColor((int)B_001473C0, (int)B_001473C4, (int)B_001473C8);
    } else {
        iosSetBGColor(r, g, b);
    }
    D_00130414 = 1.0f;
}

int GetNowFogColorR(void)
{
    return B_001473B4;
}

int GetNowFogColorG(void)
{
    return B_001473B8;
}

int GetNowFogColorB(void)
{
    return B_001473B8;
}

void *getFogMode(void)
{
    return &B_00147370;
}

void *getFogNearDist(void)
{
    return B_00147374;
}

void *getFogFarDist(void)
{
    return B_00147378;
}

void *getFogNearRate(void)
{
    return B_0014737C;
}

void *getFogFarRate(void)
{
    return B_00147380;
}

void *getFogRate(void)
{
    return B_00147384;
}

void *getFogOffset(void)
{
    return B_00147388;
}

void *getFogUnderWater(void)
{
    return D_00130418;
}

void *getFogColorR(void)
{
    return B_0014738C;
}

void *getFogColorG(void)
{
    return B_00147390;
}

void *getFogColorB(void)
{
    return B_00147394;
}

void changeFogParam(void)
{
    setFogImmediate();
}
