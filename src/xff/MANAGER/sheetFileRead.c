extern void sheetFsDataRead(int, void *, int);

extern void iosJumpRecoverPoint(void *);
extern unsigned char RO_00141AB8[];

void sheetFileRead(void *arg0, void *arg1, int arg2) {
    int temp_v0;
    void *temp_s0;

    temp_s0 = *(void **)arg0;
    sheetFsDataRead((*(int *)((char *)(temp_s0) + 0)), arg1, arg2);
    temp_v0 = (*(int *)((char *)(temp_s0) + 8)) + arg2;
    (*(int *)((char *)(temp_s0) + 8)) = temp_v0;
    if ((*(int *)((char *)(temp_s0) + 4)) < temp_v0) {
        iosJumpRecoverPoint(RO_00141AB8);
    }
}
