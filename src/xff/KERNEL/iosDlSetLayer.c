typedef struct { int a, b; int chain[2]; int c; int n; int cur; int layer; } DlState;
extern volatile DlState B_00065018;
extern unsigned char RO_00042FA0[];
extern void LoaderSysPrintf(void *, ...);

void iosDlSetLayer(int l)
{
    if (l < 0)
        LoaderSysPrintf(RO_00042FA0);
    else if (l >= B_00065018.n)
        l = B_00065018.n - 1;
    B_00065018.layer = l;
}
