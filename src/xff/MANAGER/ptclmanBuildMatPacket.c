#ifdef NONMATCHING /* GS TEST/ALPHA store order and switch zero-extension paths differ (~70 diffs) */
typedef unsigned int u64 __attribute__((mode(DI)));

typedef struct {
    char *base;
    int count;
} PtclPacket;

extern PtclPacket B_001487A8;

void ptclmanBuildMatPacket(int mode, float u, float v)
{
    char *p = B_001487A8.base + B_001487A8.count * 16;
    u64 *q;
    unsigned int a;
    int b;

    q = (u64 *)(p + 0x20);
    q[0] = 0x51011;
    q[1] = 0x47;
    q = (u64 *)(p + 0x30);
    q[1] = 8;
    q[0] = (u64)(u <= 1.0f ? 1 : 0) | ((u64)(v <= 1.0f ? 1 : 0) << 2);
    switch (mode) {
    default:
    case 0:
        a = 0;
        b = 1;
        break;
    case 1:
        a = 0;
        b = 2;
        break;
    case 2:
        a = 2;
        b = 0;
        break;
    }
    q = (u64 *)(p + 0x40);
    q[0] = (u64)a | ((u64)b << 2) | ((u64)0 << 4) | ((u64)1 << 6) | ((u64)0x80 << 32);
    q[1] = 0x42;
    *(u64 *)(p + 0x18) = 0xE;
    *(int *)(p + 0x0) = 0x10000004;
    *(int *)(p + 0x8) = 0x13000000;
    *(int *)(p + 0xC) = 0x50000004;
    *(u64 *)(p + 0x10) = ((u64)0x10000000 << 32) | 0x8003;
    *(int *)(p + 0x4) = 0;
    B_001487A8.count += 5;
}
#endif
