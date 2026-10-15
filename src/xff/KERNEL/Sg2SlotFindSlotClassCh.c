typedef struct { int flags; int a, b, cls, c, ch; char pad[0xC8]; } Sg2Slot;
extern Sg2Slot B_000DE370[];

int Sg2SlotFindSlotClassCh(int *out, int cls, int ch)
{
    int n = 0;
    int i;
    for (i = 0; i < 48; i++) {
        if ((B_000DE370[i].flags & 1) && B_000DE370[i].cls == cls && B_000DE370[i].ch == ch) {
            *out++ = i;
            n++;
        }
    }
    return n;
}
