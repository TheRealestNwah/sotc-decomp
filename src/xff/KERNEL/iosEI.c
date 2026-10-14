extern int EIntr();
extern void iosJumpRecoverPoint(void *);
extern int D_00040634;
extern unsigned char RO_00041F98[1];
extern unsigned char RO_00041FC8[1];

int iosEI(void)
{
    int temp_v0;

    temp_v0 = D_00040634 - 1;
    D_00040634 = temp_v0;
    if (temp_v0 == 0) {
        if (EIntr() != 0) {
            iosJumpRecoverPoint(&RO_00041F98);
        }
    } else if (temp_v0 < 0) {
        iosJumpRecoverPoint(&RO_00041FC8);
    }
    return D_00040634;
}
