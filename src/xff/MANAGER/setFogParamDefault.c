typedef struct FogParameter {
    int mode;
    float near;
    float far;
    float min;
    float max;
    float rate;
    int r;
    int g;
    int b;
    int a;
} FogParameter;
extern FogParameter D_001303E8;
extern FogParameter B_00147398;
extern FogParameter B_00147370;

void setFogParamDefault(void)
{
    B_00147398 = D_001303E8;
    B_00147370 = B_00147398;
}
