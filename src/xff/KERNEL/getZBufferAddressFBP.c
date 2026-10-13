extern unsigned char B_00065550[1];

int getZBufferAddressFBP(void)
{
    return (int) ((*(int *)((char *)(&B_00065550) + 0)) * (*(int *)((char *)(&B_00065550) + 4))) >> 0xB;
}
