typedef struct { int flags; int a, b, cls, vab, ch; int c, d, e, f; int note; char pad[0x34]; int ssa; char pad2[0x7C]; } Sg2Slot;
extern Sg2Slot B_000DE370[];

int Sg2SlotFindVabChSsaBaseNote(int *out, int x, int ch, int ssa, int note)
{
    int n = 0;
    int i;
    for (i = 0; i < 48; i++) {
        if ((B_000DE370[i].flags & 1) && B_000DE370[i].vab == x && B_000DE370[i].ch == ch && B_000DE370[i].ssa == ssa && B_000DE370[i].note == note) {
            *out++ = i;
            n++;
        }
    }
    return n;
}
