extern void DeleteTwoWayLink(char *);

void deleteGazeCtrlWork(char *p)
{
    if (*(int *)(p + 0x40) != 0) {
        *(int *)(p + 0x40) = 0;
        DeleteTwoWayLink(p + 0x34);
    }
}
