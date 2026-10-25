typedef int s128 __attribute__((mode(TI)));
typedef struct Link { struct Link *next; struct Link *prev; } Link;
extern int DeleteTwoWayLink(Link *);
extern int AddTwoWayLinkNext(int *, int *);
extern s128 IdentityQuaternion;
extern s128 ZeroVector;

static inline char *characterClass(unsigned char *object)
{
    switch (object[8]) {
    case 9: return (char *)object + 0x90;
    case 0x16: return (char *)object + 0x90;
    default: return 0;
    }
}

static inline void fillQuaternions(s128 *destination, s128 *value, int count)
{
    if (count > 0) {
        int remaining = count;
        do {
            *destination = *value;
            remaining--;
            destination++;
        } while (remaining != 0);
    }
}

void SetCharacterClassMotionAddSyncMode(char *character, unsigned char *target)
{
    if (*(int *)(character + 0xD00) != 0) {
        DeleteTwoWayLink((Link *)(character + 0xD10));
        character[0xD90] = 0;
        *(int *)(character + 0xD00) = 0;
        character[0xD91] = 0;
    }
    AddTwoWayLinkNext((int *)(characterClass(target) + 0xD04),
        (int *)(character + 0xD10));
    character[0xD90] = 2;
    *(unsigned char **)(character + 0xD00) = target;
    if (target != 0)
        character[0xD91] = characterClass(target)[0x1070];
    else
        character[0xD91] = 0;
    *(int *)(character + 0x738) = 0;
    fillQuaternions(*(s128 **)(character + 0x318), &IdentityQuaternion,
        (*(int **)(character + 0x358))[1]);
    *(s128 *)(character + 0xD60) = ZeroVector;
    *(s128 *)(character + 0xD70) = ZeroVector;
}
