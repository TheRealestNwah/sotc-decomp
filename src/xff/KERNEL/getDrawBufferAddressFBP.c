extern unsigned char B_00065550[1];

int getDrawBufferAddressFBP(void)
{
    return ((int) ((*(int *)((char *)(&B_00065550) + 0)) * (*(int *)((char *)(&B_00065550) + 4))) >> 0xB) + ((int) ((*(int *)((char *)(&B_00065550) + 8)) * (*(int *)((char *)(&B_00065550) + 0xC))) >> 0xB);
}
