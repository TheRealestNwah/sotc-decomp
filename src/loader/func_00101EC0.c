typedef unsigned int u_long128 __attribute__((mode(TI)));

extern void PutString(int attr, const char *format, ...);

extern char *D_00131D04[][2];
extern char D_00136750[];
extern char D_00136778[];
extern char D_00136788[];
extern char D_00136798[];
extern char D_001367B0[];
extern char D_001367C0[];
extern char D_00139FF0[];
extern u_long128 D_0013B780;

void func_00101EC0(int cause, int epc, int badvaddr, int a3, int t0, int *regs, unsigned int mode) {
    switch (mode) {
        case 0: {
            int i;

            PutString(0xFFC04000, D_00136778, D_00131D04[cause][0]);
            PutString(0x40FFC000, D_00136788, badvaddr);
            PutString(0x40C0FF00, D_00136798, a3, t0);
            PutString(0xC0C0C000, D_001367B0, epc);
            PutString(-0x100, D_00139FF0);
            for (i = 0; i < 8; i++) {
                PutString(0x80A0C000, D_00136750, regs[1], regs[0], regs[3], regs[2], regs[5], regs[4], regs[7],
                          regs[6]);
                regs += 8;
            }
            break;
        }
        case 1: {
            int i;

            for (i = 0; i < 16; i++) {
                D_0013B780 = (unsigned int)regs[0];
                PutString(-0x100, D_001367C0, regs[1], ((int *)&D_0013B780)[3], ((int *)&D_0013B780)[2],
                          ((int *)&D_0013B780)[1], ((int *)&D_0013B780)[0]);
                regs += 2;
            }
            break;
        }
        case 2: {
            int i;

            regs += 0x20;
            for (i = 0; i < 16; i++) {
                D_0013B780 = (unsigned int)regs[0];
                PutString(-0x100, D_001367C0, regs[1], ((int *)&D_0013B780)[3], ((int *)&D_0013B780)[2],
                          ((int *)&D_0013B780)[1], ((int *)&D_0013B780)[0]);
                regs += 2;
            }
            break;
        }
    }
}
