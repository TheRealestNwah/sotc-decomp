typedef struct {
    int flags;
    int a;
    int serial;
    int b;
    int c;
    int d;
    int e;
    char pad1C[0xE0 - 0x1C];
} Slot;

extern Slot B_000DE370[48];
extern int B_000DE360;
extern void Sg2SlotSetReverbOffBit(int hi, int bit);
extern void Sg2SlotSetNoiseOffBit(int hi, int bit);

#ifdef NONMATCHING
/* Parked: 25 words differ (register allocation of the slot field pointers) */
void Sg2SlotSetBasicParam(int a, int i, int b, int c, int d, int e)
{
    int serial = B_000DE360++;
    B_000DE370[i].flags = 1;
    B_000DE370[i].a = a;
    B_000DE370[i].b = b;
    B_000DE370[i].c = c;
    B_000DE370[i].d = d;
    B_000DE370[i].e = e;
    B_000DE370[i].serial = serial;
    Sg2SlotSetReverbOffBit(i >= 24, i < 24 ? 1 << i : 1 << (i - 24));
    Sg2SlotSetNoiseOffBit(i >= 24, i < 24 ? 1 << i : 1 << (i - 24));
}
#endif
