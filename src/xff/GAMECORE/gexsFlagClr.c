extern unsigned char B_00184458[];

void gexsFlagClr(int a, int b)
{
    unsigned char *base = B_00184458;
    unsigned char *p;
    int bit;

    if (a >= 100 || b >= 64) {
        p = 0;
    } else {
        int n = a * 64 + b;

        bit = n & 7;
        p = base + (n >> 3);
    }
    if (p != 0)
        *p &= ~(1 << (bit & 7));
}
