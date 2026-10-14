extern void *GetSCRCharaAIWorkPtr(void *);
extern void *getSCRDataCtrlWork(void *);

#define NULL ((void *)0)
extern void func_000940A0(void *, void *);
extern void *getRootPointDataByAreaIdx(void *, int, int);
extern unsigned char RO_0017F688[];

void SCRFuncPoseidonModifyGP2AttainPos(void *arg0) {
    void *var_s0;
    int temp_v1;
    int var_s1;
    void *temp_s2;
    void *temp_s4;
    void *temp_v0;

    temp_s4 = GetSCRCharaAIWorkPtr(arg0);
    temp_v0 = getSCRDataCtrlWork(arg0);
    temp_s2 = getRootPointDataByAreaIdx(temp_v0, (*(int *)((char *)(temp_v0) + 0x3C88)), (*(int *)((char *)(temp_v0) + 0x3C8C)));
    if ((*(int *)((char *)(temp_v0) + 0x4094)) != 0) {
        (*(int *)((char *)(temp_s4) + 0x41B4)) = 1;
    } else if (temp_s2 != NULL) {
        if ((*(int *)((char *)(temp_s4) + 0x41B4)) != 0) {
            var_s1 = 4;
            var_s0 = RO_0017F688;
            do {
                temp_v1 = (*(int *)((char *)(temp_s2) + 0x10));
                if (temp_v1 != (*(int *)((char *)(var_s0) + 0))) {
                    if (temp_v1 == (*(int *)((char *)(var_s0) + 4))) {
                        goto block_9;
                    }
                } else {
block_9:
                    func_000940A0(arg0, var_s0);
                }
                var_s1 -= 1;
                var_s0 += 0x20;
            } while (var_s1 >= 0);
        }
        (*(int *)((char *)(temp_s4) + 0x41B4)) = 0;
    }
}
