typedef int s128 __attribute__((mode(TI)));

typedef union CharacterClass {
    struct {
    char pad0[0x134];
    s128 *pos;
    char pad138[0x35C - 0x138];
    unsigned char fallDown;
    unsigned char fallDownPrev;
    char pad35E[0x51C - 0x35E];
    int fallDownTime;
    char pad520[0x10A7 - 0x520];
    unsigned char fallDownLanding;
    char pad10A8[0x10B0 - 0x10A8];
    s128 fallDownPos;
    } s;
} CharacterClass;

void ResetCharacterClassFallDownInfo(CharacterClass *cls)
{
    cls->s.fallDownPrev = 0;
    cls->s.fallDown = 0;
    cls->s.fallDownLanding = 0;
    cls->s.fallDownTime = 0;
    cls->s.fallDownPos = *cls->s.pos;
}
