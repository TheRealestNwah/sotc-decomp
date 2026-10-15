extern int DIntr();
extern void iosJumpRecoverPoint(void *, int);
extern int D_00040634;
extern unsigned char RO_00041F68[];
extern unsigned char RO_00041F80[];

void iosDI(void)
{
    if (DIntr() != 0) {
        if (D_00040634 != 0) {
            iosJumpRecoverPoint(RO_00041F68, D_00040634);
        }
    } else if (D_00040634 <= 0) {
        iosJumpRecoverPoint(RO_00041F80, D_00040634);
    }
    D_00040634 += 1;
}
