typedef struct {
    int flags;
    int alloc;
    char pad8[0xD8];
} Sg2Slot;

extern Sg2Slot B_000DE370[];

void Sg2SlotTbl(int n, char *buf)
{
    int i;
    int j = 0;
    char c;

    for (i = n * 24; i < n * 24 + 24; i++) {
        c = '-';
        if (B_000DE370[i].alloc != 0)
            c = B_000DE370[i].alloc + '0';
        buf[j++] = c;
        if (i != 0 && i != 24 && i % 4 == 3)
            buf[j++] = ' ';
    }
    buf[j] = 0;
}
