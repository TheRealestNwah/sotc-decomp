extern unsigned char *B_000C5C0C;
extern char *B_000C5C10;

static void func_000246D8(void)
{
    unsigned char *ev = B_000C5C0C;
    *(float *)(B_000C5C10 + (ev[0] & 0xF) * 0x70 + 0x2EC) = ev[2] / 12.0;
}
