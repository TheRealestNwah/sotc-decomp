extern void *D_0017AEA0;
extern int D_0017AEA4;
extern int D_0017AEA8;
extern int D_0017AEAC;
extern void *D_0017AEC0;
extern int D_0017AEC4;
extern int func_00081248(float *pos, int param, float *prev);

void nico_setPlayerDemoAdditionClothCollisionFloorTable(void)
{
    D_0017AEA0 = &func_00081248;
    D_0017AEA4 = 0;
    D_0017AEA8 = 0;
    D_0017AEAC = 0;
    D_0017AEC0 = &func_00081248;
    D_0017AEC4 = 0;
}
