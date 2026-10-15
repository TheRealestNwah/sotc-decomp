typedef struct {
    int a, b;
    int adrs[2];
    int ptr;
    int e;
    int cur;
} DlBufs;

extern volatile DlBufs B_00065018;

int iosDlGetTransAdrs(void)
{
    volatile DlBufs *dl = &B_00065018;

    return dl->adrs[dl->cur];
}
