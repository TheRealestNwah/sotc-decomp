extern int iosgluGetCameraContext(int, int, int, int);

typedef int s128 __attribute__((mode(TI)));
extern void iosCopyMatrix(void *, int);
extern unsigned char B_001487C0[];
extern int D_001360E0;
extern void *D_001360E4;

void ptclmanFrameInit(int arg0, int arg1, int arg2, int arg3) {
    int temp_a1;
    int temp_s1;
    int temp_v1;
    void *temp_v0;

    temp_s1 = iosgluGetCameraContext(arg0, arg1, arg2, arg3);
    temp_a1 = temp_s1 + 0x1A0;
    temp_v1 = D_001360E0 ^ 1;
    D_001360E0 = temp_v1;
    temp_v0 = B_001487C0 + (temp_v1 * 0x120);
    D_001360E4 = temp_v0;
    iosCopyMatrix(temp_v0, temp_a1);
    iosCopyMatrix(D_001360E4 + 0x40, temp_s1 + 0x4A0);
    iosCopyMatrix(D_001360E4 + 0x80, temp_s1 + 0x660);
    iosCopyMatrix(D_001360E4 + 0xC0, temp_s1 + 0x5A0);
    (*(s128 *)((char *)(D_001360E4) + 0x100)) = (s128) (*(s128 *)((char *)(temp_s1) + 0x140));
    (*(s128 *)((char *)(D_001360E4) + 0x110)) = (s128) (*(s128 *)((char *)(temp_s1) + 0x150));
}
