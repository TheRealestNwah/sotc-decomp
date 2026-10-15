extern int Sg2VabHdClose(int);

int Sg2VabInit(void)
{
    int i;
    for (i = 0; i < 8; i++)
        Sg2VabHdClose(i);
    return 0;
}
