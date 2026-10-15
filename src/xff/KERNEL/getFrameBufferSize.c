extern unsigned char B_00065550[];

int getFrameBufferSize(void)
{
    return ((*(int *)((char *)(B_00065550) + 0)) * (*(int *)((char *)(B_00065550) + 4))) + ((*(int *)((char *)(B_00065550) + 8)) * (*(int *)((char *)(B_00065550) + 0xC)) * 2);
}
