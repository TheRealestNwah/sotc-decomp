int changedDPGroupID(int a, char *p, int g, int h)
{
    int r = 0;

    if (g == *(int *)(p + 0x3C68)) {
        if (h != *(int *)(p + 0x3C6C)) {
            r = 1;
        }
    } else {
        r = 1;
    }
    return r;
}
