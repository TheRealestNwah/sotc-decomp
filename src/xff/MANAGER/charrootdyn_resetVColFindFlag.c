extern void DeleteTwoWayLink(void *);
void charrootdyn_resetVColFindFlag(char *p)
{
    if (*(int *)(p + 0xF3C) != 0) {
        *(int *)(p + 0xF3C) = 0;
        DeleteTwoWayLink(p + 0xF30);
    }
}
