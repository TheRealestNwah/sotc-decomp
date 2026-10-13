extern unsigned char B_00065550[1];

int getDrawBufferAddressTBP(void)
{
    return ((int) ((*(int *)((char *)(&B_00065550) + 0)) * (*(int *)((char *)(&B_00065550) + 4))) >> 6) + ((int) ((*(int *)((char *)(&B_00065550) + 8)) * (*(int *)((char *)(&B_00065550) + 0xC))) >> 6);
}
