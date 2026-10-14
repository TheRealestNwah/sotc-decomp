typedef struct { unsigned long a : 9; unsigned int cnt : 15; unsigned long b : 40; } LF;

void modelDeleteDispModelClass(char **p)
{
    ((LF *)(*(char **)(*p + 0x20) + 0x18))->cnt--;
}
