extern void *getSCRDataCtrlWork(void *);
extern void setPassageRangeData(void *, float, float);

void SCRFuncSetPassageRangeData(void *actor, float fparg0, float fparg1) {
    setPassageRangeData(getSCRDataCtrlWork(actor), fparg0, fparg1);
}
