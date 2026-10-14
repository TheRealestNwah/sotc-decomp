extern void *GetSCRCharaAIWorkPtr(void *);

int SCRConditionUnagiDamageCheck(void *arg0, int arg1) {
    void *temp_v1;

    temp_v1 = GetSCRCharaAIWorkPtr(arg0);
    switch (arg1) {                                 /* irregular */
    case 1:
        return (*(int *)((char *)(temp_v1) + 0x5A90));
    case 0:
        return (*(int *)((char *)(temp_v1) + 0x5A8C));
    case 2:
        return (*(int *)((char *)(temp_v1) + 0x5A94));
    default:
        return 0;
    }
}
