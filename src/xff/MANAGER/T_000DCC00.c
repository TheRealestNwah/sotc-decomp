typedef struct {
    char pad0[0x38];
    unsigned long flags;
    char pad40[4];
    int count;
    char pad48[0x560 - 0x48];
} Slot;

extern int D_00139E08;
extern Slot B_0014E898[];
extern int D_00139BF4;

static void T_000DCC00(void)
{
    int i = D_00139E08;

    if (i >= 0) {
        Slot *s = &B_0014E898[i];
        D_00139E08 = -1;
        s->flags |= 0x8000UL << 22;
        s->count = 0;
    }
    D_00139BF4 = 0;
}
