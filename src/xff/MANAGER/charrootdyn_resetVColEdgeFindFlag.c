extern void DeleteTwoWayLink(void *);
void charrootdyn_resetVColEdgeFindFlag(char *p)
{
    if (*(int *)(p + 0xE70) != 0) {
        *(int *)(p + 0xE70) = 0;
        DeleteTwoWayLink(p + 0xF60);
    }
}
