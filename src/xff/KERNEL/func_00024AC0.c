extern unsigned char *B_000C5C0C;
extern char *B_000C5C10;

static void func_00024AC0(void)
{
    unsigned char *ev = B_000C5C0C;
    int v = ev[2] * 2 - 0x80;
    if (v < 0) {
        v |= 0x100;
    }
    *(short *)(B_000C5C10 + (ev[0] & 0xF) * 0x70 + 0x310) = (v << 6) & 0x7FC0;
}
