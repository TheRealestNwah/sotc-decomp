extern void *getSCRDataCtrlWork(void *);
extern int setCreateTempAttain();

int SCRFuncSetCreateTempAttain(int a, int b)
{
    return setCreateTempAttain(((int)getSCRDataCtrlWork((void *)a)), b);
}
