extern unsigned char *B_000C5C0C;
extern char *B_000C5C10;
extern void Sg2SlotModKeyOff(int, int, int);

static void func_000231C8(void)
{
    unsigned char *ev = B_000C5C0C;
    Sg2SlotModKeyOff(*(int *)(B_000C5C10 + 4), ev[0] & 0xF, ev[1]);
}
