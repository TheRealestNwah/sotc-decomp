extern unsigned char *B_000C5C0C;
extern char *B_000C5C10;

static void func_00024D38(void)
{
    unsigned char *ev = B_000C5C0C;
    *(B_000C5C10 + (ev[0] & 0xF) * 0x70 + 0x314) = ev[2];
}
