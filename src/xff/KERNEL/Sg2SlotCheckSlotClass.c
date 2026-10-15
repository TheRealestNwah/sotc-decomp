typedef struct { int flags; int a, b, cls; char pad[0xD0]; } Sg2Slot;
extern Sg2Slot B_000DE370[];

int Sg2SlotCheckSlotClass(int cls)
{
    int r = 0;
    int i;
    Sg2Slot *s = B_000DE370;
    for (i = 0; i < 48; i++, s++) {
        if ((s->flags & 1) && s->cls == cls) {
            r = 1;
            break;
        }
    }
    return r;
}
