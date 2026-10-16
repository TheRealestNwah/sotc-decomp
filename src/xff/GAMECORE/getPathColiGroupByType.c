extern int B_001A03E0;
extern int B_001A03E4;

int getPathColiGroupByType(int type)
{
    if (type == 0)
        return B_001A03E0;
    if (type == 1)
        return B_001A03E4;
    return 0;
}
