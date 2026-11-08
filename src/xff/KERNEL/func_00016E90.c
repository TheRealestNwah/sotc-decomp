extern int isceGsPutIMR(int);
extern volatile long D_00040BA8;
extern void (*D_00040BBC)(void);

static int func_00016E90(void)
{
    int imr;

    imr = isceGsPutIMR(0xFF00);
    D_00040BA8++;
    if (D_00040BBC != 0) {
        D_00040BBC();
    }
    *(volatile long *)0x12001000 |= 2;
    isceGsPutIMR(imr);
    __asm__ volatile("sync\n\tei");
    return 0;
}
