void isysSetObjImmediateDeleteFunc(void *arg0, int arg1)
{
    (*(int *)((char *)(arg0) + 0x18)) = arg1;
}
