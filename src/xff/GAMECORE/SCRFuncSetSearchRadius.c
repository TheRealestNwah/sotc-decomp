extern void *getSCRDataCtrlWork(void *);
extern int setSearchRadius(int, float);

int SCRFuncSetSearchRadius(void *actor, float r)
{
    return setSearchRadius(((int)getSCRDataCtrlWork(actor)), r);
}
