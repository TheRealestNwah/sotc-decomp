extern int getPathColiGroupByType(int);

int getPathColiGroup(void *work)
{
    return getPathColiGroupByType(*(int *)((char *)work + 0x3C50));
}
