extern unsigned char B_001487A8[];

int ptclmanGet(void)
{
    return (*(int *)((char *)(B_001487A8) + 0)) + ((*(int *)((char *)(B_001487A8) + 4)) * 0x10);
}
