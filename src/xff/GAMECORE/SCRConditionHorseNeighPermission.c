extern void *getSCRDataCtrlWork(void *);

int SCRConditionHorseNeighPermission(void *arg0, float fparg0) {
    return ((int) ((*(float *)((char *)(getSCRDataCtrlWork(arg0)) + 0x40A4)) * 10.0f) % (int) (fparg0 * 10.0f)) == 0;
}
