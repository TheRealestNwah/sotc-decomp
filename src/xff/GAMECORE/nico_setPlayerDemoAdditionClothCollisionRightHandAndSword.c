extern unsigned char B_0018B740[];
extern int func_00080E68(float *pos, int param, float *prev);
extern void *D_0017AEA0;
extern void *D_0017AEA4;
extern int D_0017AEA8;
extern int D_0017AEAC;
extern int D_0017AEC0;
extern int D_0017AEC4;

void nico_setPlayerDemoAdditionClothCollisionRightHandAndSword(int arg0)
{
    *(int *)B_0018B740 = arg0;
    *(float *)(B_0018B740 + 4) = 0.03f;
    D_0017AEA0 = &func_00080E68;
    D_0017AEA4 = &B_0018B740;
    D_0017AEA8 = 0;
    D_0017AEAC = 0;
    D_0017AEC0 = 0;
    D_0017AEC4 = 0;
}
