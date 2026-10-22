typedef struct Link { struct Link *next; struct Link *prev; } Link;
extern int DeleteTwoWayLink(Link *);

void ResetCharacterClassSyncMode(char *c)
{
    if (*(int *)(c + 0xD00) != 0) {
        DeleteTwoWayLink((Link *)(c + 0xD10));
        c[0xD90] = 0;
        *(int *)(c + 0xD00) = 0;
        c[0xD91] = 0;
    }
}
