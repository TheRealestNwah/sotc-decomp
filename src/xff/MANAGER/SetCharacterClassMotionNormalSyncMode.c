typedef struct Link { struct Link *next; struct Link *prev; } Link;
extern int DeleteTwoWayLink(Link *);
extern int AddTwoWayLinkNext(int *, int *);

static inline char *characterClass(unsigned char *object)
{
    switch (object[8]) {
    case 9: return (char *)object + 0x90;
    case 0x16: return (char *)object + 0x90;
    default: return 0;
    }
}

void SetCharacterClassMotionNormalSyncMode(char *character, unsigned char *target)
{
    if (*(int *)(character + 0xD00) != 0) {
        DeleteTwoWayLink((Link *)(character + 0xD10));
        character[0xD90] = 0;
        *(int *)(character + 0xD00) = 0;
        character[0xD91] = 0;
    }
    AddTwoWayLinkNext((int *)(characterClass(target) + 0xD04),
        (int *)(character + 0xD10));
    character[0xD90] = 1;
    *(unsigned char **)(character + 0xD00) = target;
    if (target != 0)
        character[0xD91] = characterClass(target)[0x1070];
    else
        character[0xD91] = 0;
}
