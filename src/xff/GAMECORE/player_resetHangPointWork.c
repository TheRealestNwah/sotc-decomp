typedef struct Link { struct Link *next; struct Link *prev; } Link;
extern int DeleteTwoWayLink(Link *);

void player_resetHangPointWork(char *p)
{
    if (*(int *)(p + 0x0) != 0) {
        *(int *)(p + 0x0) = 0;
        DeleteTwoWayLink((Link *)(p + 0x50));
    }
}
