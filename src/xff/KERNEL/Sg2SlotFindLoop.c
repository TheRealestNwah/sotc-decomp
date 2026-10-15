typedef struct { int flags; char pad[0xDC]; } Sg2Slot;
extern Sg2Slot B_000DE370[];

int Sg2SlotFindLoop(int *out)
{
    int n = 0;
    int i;
    for (i = 0; i < 48; i++) {
        if (B_000DE370[i].flags & 4) {
            *out++ = i;
            n++;
        }
    }
    return n;
}
