extern unsigned char B_00065550[1];

int getFrameBufferSizeFBP(void)
{
    return (int) (((*(int *)((char *)(&B_00065550) + 0)) * (*(int *)((char *)(&B_00065550) + 4))) + ((*(int *)((char *)(&B_00065550) + 8)) * (*(int *)((char *)(&B_00065550) + 0xC)) * 2)) >> 0xB;
}
