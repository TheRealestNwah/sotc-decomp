typedef struct {
    char pad0[0x14];
    volatile int max;
    char pad18[4];
    int layer;
} PathState;

extern int D_00040B00;
extern PathState B_00065018;
extern int B_00065048[];
extern char RO_00042FE0[];
extern char RO_00042FA0[];
extern void LoaderSysPrintf(const char *, ...);

int iosDlPopLayer(void)
{
    int layer;

    if (--D_00040B00 < 0)
        LoaderSysPrintf(RO_00042FE0, B_00065018.layer, B_00065048[D_00040B00]);
    layer = B_00065048[D_00040B00];
    if (layer < 0)
        LoaderSysPrintf(RO_00042FA0);
    else if (layer >= B_00065018.max)
        layer = B_00065018.max - 1;
    B_00065018.layer = layer;
    return B_00065048[D_00040B00];
}
