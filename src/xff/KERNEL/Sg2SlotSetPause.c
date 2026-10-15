typedef struct { unsigned int flags; char pad[0xDC]; } Sg2Slot;
extern Sg2Slot B_000DE370[];

void Sg2SlotSetPause(int i, int on)
{
    if (on != 0)
        B_000DE370[i].flags |= 0x4000;
    else
        B_000DE370[i].flags &= ~0x4000;
    B_000DE370[i].flags |= 0x80;
}
