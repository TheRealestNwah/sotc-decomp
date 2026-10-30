extern unsigned char *B_000C5C0C;
extern char *B_000C5C10;

static void func_00024B68(void)
{
    int ch = B_000C5C0C[0] & 0xF;
    if (B_000C5C0C[2] >= 0x20) {
        B_000C5C0C[2] = 0x1F;
    }
    *(short *)(B_000C5C10 + ch * 0x70 + 0x312) = (B_000C5C0C[2] >> 2) & 0x1F;
}
