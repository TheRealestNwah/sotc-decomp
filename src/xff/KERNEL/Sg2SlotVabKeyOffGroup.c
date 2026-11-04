typedef struct {
    int flags;
    char pad4[0x10 - 4];
    int vab;
    char pad14[0x1C - 0x14];
    int group;
    char pad20[0xE0 - 0x20];
} Slot;

extern Slot B_000DE370[48];
extern int B_000DE338[2];
extern int DIntr(void);
extern int EIntr(void);
extern int Sg2SlotSetAdsr(int, unsigned short, unsigned short);

void Sg2SlotVabKeyOffGroup(int vab, int group)
{
    int interrupt = DIntr();
    int i;
    for (i = 0; i < 48; i++) {
        if ((B_000DE370[i].flags & 1) && B_000DE370[i].vab == vab && B_000DE370[i].group == group) {
            int low;
            Sg2SlotSetAdsr(i, 0, 8);
            low = i < 24;
            B_000DE338[low ? 0 : 1] |= low ? 1 << i : 1 << (i - 24);
            B_000DE370[i].group = -1;
        }
    }
    if (interrupt)
        EIntr();
}
