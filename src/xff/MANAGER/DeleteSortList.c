extern void iosFree(int address);
void DeleteSortList(int address)
{
    int *list = (int *)address;
    iosFree(list[0]);
    iosFree(address);
}
