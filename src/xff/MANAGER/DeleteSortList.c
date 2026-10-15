extern void iosFree(void *p);

void DeleteSortList(void **list)
{
    iosFree(list[0]);
    iosFree(list);
}
