extern volatile int B_000C5B38;
extern int B_000C5B3C;
extern int B_000C5B40[48];
extern int Sg2StAdpcmInit(); /* defined with no parameters; the original passes 0 */

void Sg2ExStAdpcmInit(void)
{
    int i;

    for (i = 47; i >= 0; i--) {
        B_000C5B40[i] = 0;
    }
    Sg2StAdpcmInit(0);
    B_000C5B38 = 1;
    B_000C5B3C = 0;
}
