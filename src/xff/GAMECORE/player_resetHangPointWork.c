extern void DeleteTwoWayLink(char *);

void player_resetHangPointWork(char *p)
{
    if (*(int *)(p + 0x0) != 0) {
        *(int *)(p + 0x0) = 0;
        DeleteTwoWayLink(p + 0x50);
    }
}
