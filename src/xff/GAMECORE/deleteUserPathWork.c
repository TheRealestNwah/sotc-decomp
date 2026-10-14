extern void DeleteTwoWayLink(char *);

void deleteUserPathWork(char *p)
{
    if (*(int *)(p + 0xA4) != 0) {
        *(int *)(p + 0xA4) = 0;
        DeleteTwoWayLink(p + 0x98);
    }
}
