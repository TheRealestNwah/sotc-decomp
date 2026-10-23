typedef struct {
    char pad[0x138];
    float frame;
} MotionState;

/* The char member makes every access through this type alias every other,
   which keeps the original's store and load order. */
typedef union {
    struct {
        char pad[0x720];
        int f720;
        float f724;
        int f728;
        int f72C;
        char pad730[0xC];
        float f73C;
        float f740;
        float f744;
        char pad748[0x1140 - 0x748];
        MotionState *motion;
    } s;
    char alias;
} CharacterClass;

void ResetCharacterClassMotInterpInfo(CharacterClass *chr)
{
    chr->s.f720 = 0;
    chr->s.f724 = 1.0f;
    chr->s.f728 = 0;
    chr->s.f72C = 0;
    chr->s.f73C = 1.0f;
    chr->s.f740 = chr->s.motion->frame;
    chr->s.f744 = 1.0f;
}
