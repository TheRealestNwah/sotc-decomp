extern void *D_0017AEA0;
extern int D_0017AEA4;
extern void * D_0017AEA8;
extern int D_0017AEAC;
extern void *D_0017AEC0;
extern int D_0017AEC4;
extern int func_00081640(float *pos, int param, float *prev);

void nico_setPlayerDemoAdditionClothCollisionEvisFloor(void)
{
    D_0017AEA0 = &func_00081640;
    D_0017AEA4 = 0;
    D_0017AEA8 = &func_00081640;
    D_0017AEAC = 0;
    D_0017AEC0 = &func_00081640;
    D_0017AEC4 = 0;
}
