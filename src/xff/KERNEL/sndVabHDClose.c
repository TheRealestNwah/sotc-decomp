extern int Sg2VabClose();

int sndVabHDClose(int *p)
{
    return Sg2VabClose(p[1]);
}
