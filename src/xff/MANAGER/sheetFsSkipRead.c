extern void iosCdStSkip(long);

void sheetFsSkipRead(int context, long size)
{
    iosCdStSkip(size);
}
