void bgmPlay(void *arg0, float fparg0)
{
    (*(float *)((char *)(arg0) + 0xC)) = fparg0;
    (*(int *)((char *)(arg0) + 0x24)) = (int) ((*(int *)((char *)(arg0) + 0x24)) | 1);
}
