typedef int s128 __attribute__((mode(TI)));
extern s128 B_001885D0;
extern s128 B_001885E0;
extern int D_0017A2C4;
extern int D_0017A2C8;

void reloadStageWithPlayerPos(int arg0, int arg1, s128 *arg2, s128 *arg3) {
    if (arg0 != 0) {
        D_0017A2C4 = arg0;
        D_0017A2C8 = arg1;
        B_001885D0 = *arg2;
        B_001885E0 = *arg3;
    }
}
