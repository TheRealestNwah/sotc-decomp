extern int GetCollisionFinderWorkSize(int);
int GetCalcNumObjWorkSize(int objs, int chars, int groups, int finder, int extended)
{
    int size = objs * 0x108 + 0x33;
    if (groups != 0)
        size += (groups << 3) + (objs * 0x10 + 0x80) * groups + 0x66;
    if (chars != 0) {
        if (extended != 0)
            size += chars * 0x17A + 0x33;
        else
            size += chars * 0x12A + 0x33;
    }
    size += 0x333;
    return size + GetCollisionFinderWorkSize(finder);
}
