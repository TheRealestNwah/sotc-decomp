typedef struct {
    int mode;
    int a0;
    void *buf;
    int a1;
    int size;
    int x14;
    char pad18[0x1A0 - 0x18];
    int x1A0;
    int x1A4;
    int x1A8;
    char pad1AC[0x1C4 - 0x1AC];
    int x1C4;
    int x1C8;
    int x1CC;
    int x1D0;
} PcmIn;
extern PcmIn B_000E2518[];

static int func_0002ED18(void)
{
    int i;

    for (i = 0; i < 4; i++) {
        if (B_000E2518[i].a0 == 0)
            return i;
    }
    return -1;
}

