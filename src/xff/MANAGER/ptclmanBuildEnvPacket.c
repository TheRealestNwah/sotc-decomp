#ifdef NONMATCHING
/* 47 diffs (permuter best 1415): constant materialisation order and register allocation differ */
typedef int s128 __attribute__((mode(TI)));

typedef struct {
    char *base;
    int count;
    int type;
} PacketBuf;

extern PacketBuf B_001487A8;
extern s128 D_001360D0;
extern int D_001360E4;

extern void iosCopyMatrix(void *, int);
extern float getFogFactor0(void);
extern float getFogFactor1(void);

void ptclmanBuildEnvPacket(s128 *a, int type, int matrix, s128 *b, s128 *c)
{
    char *head = B_001487A8.base + B_001487A8.count * 16;
    char *p = head + 0x20;

    B_001487A8.type = type;
    *(int *)(head + 0) = 0x30000012;
    *(int *)(head + 8) = 0x13000000;
    *(int *)(head + 0xC) = 0x6C120000;
    *(int *)(head + 0x10) = 0x1000000B;
    *(int *)(head + 0x1C) = 0x6C0A0012;
    *(int *)(head + 4) = D_001360E4 & 0x0FFFFFFF;
    *(int *)(head + 0x14) = 0;
    *(int *)(head + 0x18) = 0;
    iosCopyMatrix(p, matrix);
    *(s128 *)(p + 0x50) = D_001360D0;
    *(s128 *)(p + 0x60) = *a;
    *(float *)(p + 0x70) = getFogFactor0();
    *(float *)(p + 0x7C) = getFogFactor1();
    *(int *)(p + 0x40) = type;
    if (b != 0)
        *(s128 *)(p + 0x80) = *b;
    if (c != 0)
        *(s128 *)(p + 0x90) = *c;
    *(int *)(p + 0xAC) = 0x01000101;
    *(int *)(p + 0xA0) = 0x15000000;
    *(int *)(p + 0xA4) = 0x03000028;
    *(int *)(p + 0xA8) = 0x0200018C;
    B_001487A8.count = B_001487A8.count + 0xD;
}
#endif
