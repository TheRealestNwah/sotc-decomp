extern void *getSCRDataCtrlWork(void *);
extern void setSCRAttainRange(void *, unsigned int *);

void SCRFuncSetAttainRange(void *a, int b, int c, int d, int e, int f, int g, unsigned int *h)
{
    setSCRAttainRange(getSCRDataCtrlWork(a), h);
}
