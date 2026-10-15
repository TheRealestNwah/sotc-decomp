extern char *iosGetPacketPtrPath1(void);
extern char *iosDlGetEndAdrs(void);

char *ptclDisplayListGet(int n)
{
    char *p = iosGetPacketPtrPath1();
    if (iosDlGetEndAdrs() < p + n * 48)
        return 0;
    return p;
}
