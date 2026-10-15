typedef struct { int flags; int a, b, c, cls, ch; int d, e, f; int note; char pad[0xB8]; } Sg2Slot;
extern Sg2Slot B_000DE370[];

int Sg2SlotFindVabChNote(int *out, int cls, int ch, int note)
{
    int n = 0;
    int i;
    Sg2Slot *s = B_000DE370;
    for (i = 0; i < 48; i++, s++) {
        if ((s->flags & 1) && s->cls == cls && s->ch == ch && s->note == note) {
            *out++ = i;
            n++;
        }
    }
    return n;
}
