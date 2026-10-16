extern unsigned char B_00184138[];

int tailsFlagChk(int a, int b)
{
    int bit;
    unsigned char *base = B_00184138;
    unsigned char *p;

    if (a >= 100 || b >= 64) {
        p = 0;
    } else {
        int n = a * 64 + b;

        bit = n & 7;
        p = base + (n >> 3);
    }
    if (p != 0 && ((*p >> bit) & 1))
        return 1;
    return 0;
}
