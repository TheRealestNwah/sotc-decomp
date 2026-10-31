extern int B_001502C8;
extern int B_001502CC;
extern int B_001502D0;
extern void (*B_001502D4)(void);
extern int B_001502DC;
extern void sheetMgrDirectFileLoad(int, int, int, int, int *);

static int T_000DD730(void)
{
    int n = B_001502C8;
    int st;

    if (n > 0x10000) {
        n = 0x10000;
    }
    if (B_001502C8 <= 0) {
        return 0;
    }
    sheetMgrDirectFileLoad(B_001502CC, B_001502D0, B_001502DC, n, &st);
    while (st != 0xDEAF && st != 0xDEB0) {
        B_001502D4();
    }
    B_001502C8 -= n;
    B_001502D0 += n;
    return n;
}
