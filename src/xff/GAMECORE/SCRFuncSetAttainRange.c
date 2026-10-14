extern void *getSCRDataCtrlWork(void *);
extern int setSCRAttainRange();

int SCRFuncSetAttainRange(int a, int b, int c, int d, int e, int f, int g, int h)
{
    return setSCRAttainRange(((int)getSCRDataCtrlWork((void *)a)), h);
}
