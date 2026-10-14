extern int sheetFsDataRead(int, int, int, int);

extern void iosJumpRecoverPoint(void *);
extern unsigned char RO_00141AB8[];

void sheetFileRead(void **arg0, int arg1, int arg2, int arg3) {
    int temp_v0;
    void *temp_s0;

    temp_s0 = *arg0;
    sheetFsDataRead((*(int *)((char *)(temp_s0) + 0)), arg1, arg2, arg3);
    temp_v0 = (*(int *)((char *)(temp_s0) + 8)) + arg2;
    (*(int *)((char *)(temp_s0) + 8)) = temp_v0;
    if ((*(int *)((char *)(temp_s0) + 4)) < temp_v0) {
        iosJumpRecoverPoint(RO_00141AB8);
    }
}
