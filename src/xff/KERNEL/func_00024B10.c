extern unsigned char *B_000C5C0C;
extern char *B_000C5C10;

static void func_00024B10(void)
{
    int ch = B_000C5C0C[0] & 0xF;
    if (B_000C5C0C[2] >= 0x10) {
        B_000C5C0C[2] = 0xF;
    }
    *(short *)(B_000C5C10 + ch * 0x70 + 0x30E) = (B_000C5C0C[2] << 1) & 0xF0;
}
