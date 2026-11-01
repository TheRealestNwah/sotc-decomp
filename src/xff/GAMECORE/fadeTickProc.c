extern int D_0017A024, D_0017A020;
extern float D_0017A01C;
extern void setFade(float, float);
extern int getFade(void);
extern void sheetMgrSetNoWaitMode(int);

void fadeTickProc(void)
{
    do {
    switch (D_0017A020) {
    case 0:
        break;
    case 100:
        setFade(1.0f, D_0017A01C);
        D_0017A020++;
        sheetMgrSetNoWaitMode(1);
    case 101:
        if (getFade() == 0) {
            D_0017A020 = 0;
            D_0017A024 |= 2;
        }
        break;
    case 200:
        setFade(0.0f, D_0017A01C);
        D_0017A020++;
    case 201:
        if (getFade() == 0) {
            D_0017A020 = 0;
            D_0017A024 |= 8;
            sheetMgrSetNoWaitMode(0);
        }
        break;
    }
    } while (0);
}
