typedef struct Link { struct Link *next; struct Link *prev; } Link;
extern int DeleteTwoWayLink(Link *);
void charrootdyn_resetVColFindFlag(char *p)
{
    if (*(int *)(p + 0xF3C) != 0) {
        *(int *)(p + 0xF3C) = 0;
        DeleteTwoWayLink((Link *)(p + 0xF30));
    }
}
