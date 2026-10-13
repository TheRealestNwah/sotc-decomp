void bgmChangeVol(void *arg0, float fparg0, float fparg1)
{
    (*(float *)((char *)(arg0) + 0x14)) = fparg1;
    (*(float *)((char *)(arg0) + 0x10)) = fparg0;
    (*(int *)((char *)(arg0) + 0x24)) = (int) ((*(int *)((char *)(arg0) + 0x24)) | 2);
}
