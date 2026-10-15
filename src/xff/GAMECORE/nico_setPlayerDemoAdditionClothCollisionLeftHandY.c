extern void *D_0017AEA0;
extern int D_0017AEA4;
extern int D_0017AEA8;
extern int D_0017AEAC;
extern int D_0017AEC0;
extern int D_0017AEC4;
extern int func_00081E60(float *pos, int param, float *prev);

void nico_setPlayerDemoAdditionClothCollisionLeftHandY(int arg0)
{
    D_0017AEA0 = &func_00081E60;
    D_0017AEA4 = arg0;
    D_0017AEA8 = 0;
    D_0017AEAC = 0;
    D_0017AEC0 = 0;
    D_0017AEC4 = 0;
}
