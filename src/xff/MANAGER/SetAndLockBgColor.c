extern int D_0013041C;
extern float B_001473C0, B_001473C4, B_001473C8;
extern void iosSetBGColor(int, int, int);

void SetAndLockBgColor(int r, int g, int b)
{
    D_0013041C = 1;
    B_001473C0 = r;
    B_001473C4 = g;
    B_001473C8 = b;
    iosSetBGColor(B_001473C0, B_001473C4, B_001473C8);
}
