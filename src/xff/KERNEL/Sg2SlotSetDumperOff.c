typedef struct {
    int flags;
    int pad[2];
    int vab;
    int pad2;
    int prog;
    char pad3[0xC8];
} Slot;

extern int B_000DE338[2];
extern Slot B_000DE370[48];
extern int DIntr(void);
extern void EIntr(void);

void Sg2SlotSetDumperOff(int vab, int prog)
{
    int intr = DIntr();
    int i;

    for (i = 0; i < 48; i++) {
        if (B_000DE370[i].flags & 1) {
            if ((B_000DE370[i].flags & 8) && B_000DE370[i].vab == vab && B_000DE370[i].prog == prog) {
                int low;

                B_000DE370[i].flags &= ~8;
                low = i < 24;
                B_000DE338[low ? 0 : 1] |= low ? 1 << i : 1 << (i - 24);
            }
        }
    }
    if (intr) {
        EIntr();
    }
}
