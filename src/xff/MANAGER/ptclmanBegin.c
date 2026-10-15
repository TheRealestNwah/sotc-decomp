extern int iosGetPacketPtrPath1();
extern unsigned char B_001487A8[];

void ptclmanBegin(void)
{
    (*(int *)((char *)(B_001487A8) + 0)) = iosGetPacketPtrPath1();
    (*(int *)((char *)(B_001487A8) + 4)) = 0;
}
