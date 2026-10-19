extern void iosCdStRead(void *, int);

void sheetFsDataRead(int unused, void *buffer, int size, int unusedFlags)
{
    iosCdStRead(buffer, size);
}