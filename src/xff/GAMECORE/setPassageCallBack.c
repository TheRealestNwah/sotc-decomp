void setPassageCallBack(char *p, int a1, int a2)
{
    *(int *)(p + 0x3C44) = a2;
    *(int *)(p + 0x3C48) = a1;
}
