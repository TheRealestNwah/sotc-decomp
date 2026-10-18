

extern int GetThreadId();
extern void SignalSema(int);
extern void WaitSema(int);
extern int B_000BF6CC;
extern int D_00040D5C;
extern int D_00040D60;

void isysGroupForExit(void *arg0, int reserved) {
    int temp_v0;
    int temp_v1;

    temp_v0 = GetThreadId();
    if (temp_v0 == D_00040D5C) {
        D_00040D60 += 1;
    } else {
        WaitSema(B_000BF6CC);
        D_00040D5C = temp_v0;
        D_00040D60 = 1;
    }
    (*(unsigned char *)((char *)(arg0) + 9)) = (unsigned char) ((*(unsigned char *)((char *)(arg0) + 9)) + 0xFF);
    temp_v1 = D_00040D60 - 1;
    D_00040D60 = temp_v1;
    if (temp_v1 == 0) {
        D_00040D5C = -1;
        SignalSema(B_000BF6CC);
    }
}
