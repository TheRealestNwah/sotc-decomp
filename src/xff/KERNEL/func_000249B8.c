extern unsigned char *B_000C5C0C;
extern char *B_000C5C10;

static void func_000249B8(void)
{
    unsigned char *ev = B_000C5C0C;
    *(int *)(B_000C5C10 + (ev[0] & 0xF) * 0x70 + 0x2D0) = ev[2];
}
