extern void *getSCRDataCtrlWork(void *);
extern int changedAPIndex();

int SCRConditionAPChanged(int a)
{
    return changedAPIndex(a, ((int)getSCRDataCtrlWork((void *)a)));
}
