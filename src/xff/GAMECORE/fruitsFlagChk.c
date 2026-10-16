extern unsigned char B_00183FA8[];

int fruitsFlagChk(unsigned int a, int b)
{
    unsigned char *base = B_00183FA8;
    unsigned char *p;
    int bit;

    if (a >= 100 || b >= 32 || b < 0) {
        p = 0;
    } else {
        int n = a * 32 + b;

        bit = n & 7;
        p = base + (n >> 3);
    }
    if (p != 0 && ((*p >> bit) & 1))
        return 1;
    return 0;
}
