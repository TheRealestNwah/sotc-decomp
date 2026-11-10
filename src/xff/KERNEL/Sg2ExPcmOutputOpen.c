typedef struct {
    int open;
    int unk4;
    int arg1;
    void *buf;
    int size10;
    int size14;
    int unk18;
    char pad1C[0x1A4 - 0x1C];
    int arg0;
    int size1A8;
    int unk1AC;
    int unk1B0;
} PcmOut;

extern PcmOut B_000E2360;
extern void *malloc(int size);
extern int DIntr(void);
extern int EIntr(void);
extern void Sg2ExPcmOutputBufferClear(void);
extern void Sg2ExPcmOutputAutoFilterInit(int a);

int Sg2ExPcmOutputOpen(int arg0, int arg1, int size)
{
    PcmOut *p = &B_000E2360;
    int intr;

    if (p->buf != 0) {
        return -1;
    }
    p->buf = malloc(size / 2 * 4);
    if (p->buf == 0) {
        return -2;
    }
    intr = DIntr();
    p->size1A8 = size;
    p->arg0 = arg0;
    p->arg1 = arg1;
    p->unk1B0 = 0;
    p->size10 = size;
    p->size14 = size;
    p->unk18 = 0;
    Sg2ExPcmOutputBufferClear();
    p->unk18 = 0;
    p->unk1AC = 0;
    Sg2ExPcmOutputAutoFilterInit(0);
    Sg2ExPcmOutputAutoFilterInit(1);
    p->open = 1;
    if (intr) {
        EIntr();
    }
    return 0;
}
