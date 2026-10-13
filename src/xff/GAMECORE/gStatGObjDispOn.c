void gStatGObjDispOn(void *arg0)
{
    (*(int *)((char *)(arg0) + 0x10)) = (int) ((*(int *)((char *)(arg0) + 0x10)) | 1);
}
