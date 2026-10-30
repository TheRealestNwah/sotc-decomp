typedef struct {
    int kind;
    float near;
    float far;
    float density;
    float min;
    float max;
    int r;
    int g;
    int b;
    int a;
} FogInit;

extern char *GetWorldLayoutSheetSegHeader(void);
extern void *memset(void *, int, unsigned int);
extern void SetInitFogColClassFromStageData(FogInit *data);
extern void SeemlessInitFogTargetParamWorldLayout(void *src);

static int func_0002D948(char *p)
{
    FogInit copy;
    FogInit fog;
    char *hdr = GetWorldLayoutSheetSegHeader();
    char *layout;

    if (hdr != 0) {
        layout = *(char **)(hdr + 0x10) + *(int *)(p + 0x20) * 156;
        memset(&fog, 0, sizeof(fog));
        fog.near = *(float *)(layout + 0x20);
        fog.far = *(float *)(layout + 0x24);
        fog.density = *(float *)(layout + 0x28);
        fog.min = *(float *)(layout + 0x2C);
        fog.max = 1.0f;
        fog.r = *(unsigned char *)(layout + 0x30);
        fog.g = *(unsigned char *)(layout + 0x31);
        fog.b = *(unsigned char *)(layout + 0x32);
        fog.a = *(unsigned char *)(layout + 0x33);
        copy = fog;
        SetInitFogColClassFromStageData(&copy);
        SeemlessInitFogTargetParamWorldLayout(layout);
    }
    return 0;
}
