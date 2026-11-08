typedef struct {
    char pad0[0x14];
    volatile int max;
    char pad18[4];
    int layer;
} PathState;

extern int D_00040B00;
extern PathState B_00065018;
extern int B_00065048[];
extern char RO_00042FB8[];
extern char RO_00042FA0[];
extern void LoaderSysPrintf(const char *, ...);

/* Parked: 5 words differ, register choice only */
#ifdef NONMATCHING
void iosDlPushLayer(int layer)
{
    int i = D_00040B00;
    int n = i + 1;

    B_00065048[i] = B_00065018.layer;
    D_00040B00 = n;
    if (n >= 0x100)
        LoaderSysPrintf(RO_00042FB8, ((volatile PathState *)&B_00065018)->layer, layer);
    if (layer < 0)
        LoaderSysPrintf(RO_00042FA0);
    else if (layer >= B_00065018.max)
        layer = B_00065018.max - 1;
    B_00065018.layer = layer;
}
#else
extern void iosDlPushLayer(int layer);
#endif
