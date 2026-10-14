typedef struct { unsigned long a : 9; unsigned int cnt : 15; unsigned long b : 40; } LF;
void modelDecLinkCount(char *p)
{
    ((LF *)(p + 0x18))->cnt--;
}
