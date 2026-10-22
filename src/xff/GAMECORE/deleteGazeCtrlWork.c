typedef struct Link { struct Link *next; struct Link *prev; } Link;
extern int DeleteTwoWayLink(Link *);

void deleteGazeCtrlWork(char *p)
{
    if (*(int *)(p + 0x40) != 0) {
        *(int *)(p + 0x40) = 0;
        DeleteTwoWayLink((Link *)(p + 0x34));
    }
}
