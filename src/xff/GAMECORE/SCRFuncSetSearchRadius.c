extern void *getSCRDataCtrlWork(void *);
extern void setSearchRadius(char *, float);

void SCRFuncSetSearchRadius(void *actor, float radius)
{
    setSearchRadius(getSCRDataCtrlWork(actor), radius);
}
