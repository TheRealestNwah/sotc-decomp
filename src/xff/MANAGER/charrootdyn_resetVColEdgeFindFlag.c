typedef struct Link { struct Link *next; struct Link *prev; } Link;
extern int DeleteTwoWayLink(Link *);
void charrootdyn_resetVColEdgeFindFlag(char *p)
{
    if (*(int *)(p + 0xE70) != 0) {
        *(int *)(p + 0xE70) = 0;
        DeleteTwoWayLink((Link *)(p + 0xF60));
    }
}
