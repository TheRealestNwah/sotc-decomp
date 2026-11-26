#include "kernel/sg2slot.h"

int Sg2SlotFindVabChNote(int *out, int cls, int ch, int note)
{
    int n = 0;
    int i;
    Sg2Slot *s = B_000DE370;
    for (i = 0; i < 48; i++, s++) {
        if ((s->flags & 1) && s->vab == cls && s->ch == ch && s->note == note) {
            *out++ = i;
            n++;
        }
    }
    return n;
}
