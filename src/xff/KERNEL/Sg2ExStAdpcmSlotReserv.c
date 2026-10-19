extern int Sg2SlotFreeSearchTerm(int);
extern void Sg2SlotBlock(int, int);
extern int B_000C5B40[];
int Sg2ExStAdpcmSlotReserv(int core, int count)
{
    int reserved = 0;
    int selectedCore = core != 0;
    if (count > 0) {
        int remaining = count;
        do {
            int slot = Sg2SlotFreeSearchTerm(selectedCore);
            if (slot != -1) {
                ++reserved;
                Sg2SlotBlock(3, slot);
                B_000C5B40[slot] = 1;
            }
        } while (--remaining);
    }
    return reserved;
}