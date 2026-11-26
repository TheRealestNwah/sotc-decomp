extern int B_000C5B40[];
extern void Sg2StAdpcmQuit();
extern int Sg2SlotFreeSearchTerm(int);
extern void Sg2SlotBlock(int, int);
extern void Sg2SlotFree(int);

int Sg2ExStAdpcmSlotReserv(int core, int count);
int Sg2ExStAdpcmSlotFree(void);

void Sg2ExStAdpcmQuit(void)
{
    Sg2ExStAdpcmSlotFree();
    Sg2StAdpcmQuit();
}

int Sg2ExStAdpcmSlotMalloc(int count)
{
    return Sg2ExStAdpcmSlotReserv(0, count);
}

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

int Sg2ExStAdpcmSlotFree(void)
{
    int n = 0;
    int i;
    for (i = 0; i < 48; i++) {
        if (B_000C5B40[i] > 0) {
            Sg2SlotFree(i);
            n++;
            B_000C5B40[i] = 0;
        }
    }
    return n;
}
