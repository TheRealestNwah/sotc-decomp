int getPPointPasasgeNum(char *p)
{
    if (*(int *)(p + 0x3C60) != 9) {
        return 0;
    }
    return *(int *)(p + 0x3CB0);
}
