typedef struct { int flags; int a, b, cls, vab; char pad[0xCC]; } Sg2Slot;
extern Sg2Slot B_000DE370[];

int Sg2SlotFindVab(int *out, int v)
{
    int n = 0;
    int i;
    for (i = 0; i < 48; i++) {
        if ((B_000DE370[i].flags & 1) && B_000DE370[i].vab == v) {
            *out++ = i;
            n++;
        }
    }
    return n;
}
