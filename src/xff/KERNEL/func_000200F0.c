extern int B_000C5B40[];
extern int Sg2StAdpcmOpen(char *);
extern void Sg2SlotSetReverbOnBit(int, int);
extern void Sg2SlotSetReverbOffBit(int, int);

typedef struct {
    int magic;
    int info;
    char pad8[0x50];
    int rev[1];
} ExStHdr;

static int func_000200F0(char *st)
{
    ExStHdr *hdr = (ExStHdr *)(st + 0x28);
    unsigned long on[2];
    unsigned long off[2];
    unsigned long *p;
    unsigned long slot;
    int chunk;
    int n;
    int i;
    int j;
    int end;
    int start;
    int a3;

    n = ((short *)hdr)[3];
    chunk = 0x800 / n;
    on[1] = 0;
    on[0] = 0;
    off[1] = 0;
    off[0] = 0;
    for (i = 0; i < n; i++) {
        a3 = *(int *)(st + 0x23C);
        *(int *)(st + 0x18) = *(int *)(st + 0x230) + i * chunk;
        *(int *)(st + 0x1C) = *(int *)(st + 0x234);
        *(int *)(st + 0x20) = *(int *)(st + 0x238) + a3 * i;
        *(int *)(st + 0x24) = a3;
        if (*(int *)(st + 8) & 0x40) {
            start = 0x18;
            end = 0x30;
        } else {
            start = 0;
            end = 0x18;
        }
        for (j = start; j < end; j++) {
            if (B_000C5B40[j] == 1) {
                slot = j;
                B_000C5B40[j] = 2;
                break;
            }
        }
        if (j == end)
            return -1;
        *(int *)(st + 0x10) = slot;
        *(int *)(st + 0x14) = hdr->info;
        if (hdr->rev[i] != 0)
            on[slot / 24] |= 1 << (slot % 24);
        else
            off[slot / 24] |= 1 << (slot % 24);
        Sg2StAdpcmOpen(st + 0x10);
        *(unsigned long *)(st + 0xA0) |= (unsigned long)1 << (int)slot;
    }
    for (i = 0; i < 2; i++) {
        if (on[i] != 0)
            Sg2SlotSetReverbOnBit(i, on[i]);
        if (off[i] != 0)
            Sg2SlotSetReverbOffBit(i, off[i]);
    }
    *(int *)st = 1;
    return 0;
}
