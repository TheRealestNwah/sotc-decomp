typedef int s128 __attribute__((mode(TI)));
extern s128 D_00135B60, D_00135B70, D_00135B80;
extern s128 D_00135BA0, D_00135BB0, D_00135BC0, D_00135BD0;
extern int D_00135BE0[4];
extern s128 B_001486E0, B_001486F0, B_00148700, B_00148710;
extern int B_00148720[4];
extern void rotLightVector(int, s128 *);
extern void InitStageLightColMan(s128 *, s128 *, int);

static void func_00016710(void)
{
    int i;

    rotLightVector(0, &D_00135B60);
    rotLightVector(1, &D_00135B70);
    rotLightVector(2, &D_00135B80);
    B_001486E0 = D_00135BA0;
    B_001486F0 = D_00135BB0;
    B_00148700 = D_00135BC0;
    B_00148710 = D_00135BD0;
    for (i = 0; (unsigned int)i < 4; i++) {
        B_00148720[i] = D_00135BE0[i];
    }
    InitStageLightColMan(&D_00135B60, &B_00148710, 3);
    for (i = 0; i < 3; i++) {
        switch (i) {
        case 0:
            InitStageLightColMan(&D_00135B60, &B_001486E0, 0);
            break;
        case 1:
            InitStageLightColMan(&D_00135B70, &B_001486F0, 1);
            break;
        case 2:
            InitStageLightColMan(&D_00135B80, &B_00148700, 2);
            break;
        }
    }
}

