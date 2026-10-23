typedef struct {
    int slotClass;
    char pad[0x9AC];
} SndPort;

extern SndPort B_000C5C1C[];
extern int Sg2SlotFindSlotClass(int *, int);
extern void Sg2SlotSetKeyOffBit(int, int);

void all_keyoff(int port)
{
    int slots[48];
    int i;

    i = Sg2SlotFindSlotClass(slots, B_000C5C1C[port].slotClass) - 1;
    for (; i >= 0; i--) {
        int slot = slots[i];
        int low = slot < 24;

        Sg2SlotSetKeyOffBit(low ^ 1, low ? 1 << slot : 1 << (slot - 24));
    }
}
