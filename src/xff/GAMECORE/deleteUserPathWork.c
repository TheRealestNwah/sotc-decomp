typedef struct Link { struct Link *next; struct Link *prev; } Link;
extern int DeleteTwoWayLink(Link *);

void deleteUserPathWork(char *p)
{
    if (*(int *)(p + 0xA4) != 0) {
        *(int *)(p + 0xA4) = 0;
        DeleteTwoWayLink((Link *)(p + 0x98));
    }
}
