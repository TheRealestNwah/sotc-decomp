extern int *D_001360B8;
extern int *D_001360BC;
extern int D_001360C0;

extern void func_0001DA30(void);
extern void func_0001DB90(float);
extern float *getSpecularity(void);

void modelSetEnviroment(void)
{
    int i;

    if (D_001360B8 != 0) {
        for (i = 0; i < D_001360C0; i++) {
            D_001360B8[i] = 0;
        }
    }
    if (D_001360BC != 0) {
        for (i = 0; i < D_001360C0; i++) {
            D_001360BC[i] = 0;
        }
    }
    func_0001DA30();
    func_0001DB90(*getSpecularity());
}
