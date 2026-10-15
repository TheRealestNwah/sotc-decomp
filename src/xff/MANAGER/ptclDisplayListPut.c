extern char *iosGetPacketPtrPath1(void);
extern void iosSetPacketPtrPath1(char *);

void ptclDisplayListPut(int n)
{
    char *p = iosGetPacketPtrPath1();
    p += n * 48;
    iosSetPacketPtrPath1(p);
    p = 0;
}
