extern int iosCdStRead();

int sheetFsDataRead(int a, int b, int c, int d)
{
    return iosCdStRead(b, c, c, d);
}
