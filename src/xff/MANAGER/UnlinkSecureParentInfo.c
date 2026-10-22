typedef struct Link { struct Link *next; struct Link *prev; } Link;
extern int DeleteTwoWayLink(Link *);
void UnlinkSecureParentInfo(char *p)
{
    if (*(int *)(p + 0x4C) != 0) {
        *(int *)(p + 0x4C) = 0;
        DeleteTwoWayLink((Link *)(p + 0x40));
    }
}
