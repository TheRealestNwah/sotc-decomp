extern unsigned char *B_000C5C0C;
extern char *B_000C5C10;

static void func_00024BC0(void)
{
    int ch = B_000C5C0C[0] & 0xF;
    if ((signed char)B_000C5C0C[2] < 0) {
        B_000C5C0C[2] = 0x7F;
    }
    *(short *)(B_000C5C10 + ch * 0x70 + 0x30C) = (B_000C5C0C[2] << 8) & 0x7F00;
}
