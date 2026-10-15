extern int *ptclmanGet(void);
extern void ptclmanPut(int);
extern void iosSetPacketPtrPath1(int *);
extern int B_001487A8;
extern void iosDlChainTailCurrent(int);

void ptclmanEnd(void)
{
    int *p = ptclmanGet();
    p[0] = 0x60000000;
    p[1] = 0;
    p[2] = 0;
    p[3] = 0x13000000;
    ptclmanPut(1);
    iosSetPacketPtrPath1(ptclmanGet());
    iosDlChainTailCurrent(B_001487A8);
}
