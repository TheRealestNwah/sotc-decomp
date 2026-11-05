extern int B_001502C8;
extern int B_001502D8;
extern int B_001502DC;
extern void sheetFileRead(int, int, int);

#ifdef NONMATCHING
/* 15 diffs: register allocation of the return value */
int func_000DD6C0(void)
{
    int n;
    int ret = 0;

    n = B_001502C8 > 0x10000 ? 0x10000 : B_001502C8;
    if (B_001502C8 > 0) {
        sheetFileRead(B_001502D8, B_001502DC, n);
        ret = n;
        B_001502C8 -= n;
    }
    return ret;
}
#endif
