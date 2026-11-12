extern int B_001502C8;
extern int B_001502D8;
extern int B_001502DC;
extern void sheetFileRead(int, int, int);

static int func_000DD6C0(void)
{
    int n;
    register int ret __asm__("$2") = 0;

    n = B_001502C8 > 0x10000 ? 0x10000 : B_001502C8;
    if (B_001502C8 > 0) {
        sheetFileRead(B_001502D8, B_001502DC, n);
        B_001502C8 -= n;
        ret = n;
    }
    return ret;
}
