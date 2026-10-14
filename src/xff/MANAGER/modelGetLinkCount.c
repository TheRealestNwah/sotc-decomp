typedef struct { unsigned long a : 9; unsigned int cnt : 15; unsigned long b : 40; } LF;
int modelGetLinkCount(char *p)
{
    return ((LF *)(p + 0x18))->cnt;
}
