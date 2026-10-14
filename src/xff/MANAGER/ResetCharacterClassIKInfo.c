typedef struct {
    char pad0[0xB0];
    int unkB0;
    int unkB4;
    float weight;
    float range;
    int unkC0;
    char enable;
    char active;
    char padC6[0xA];
} IKInfo;

typedef struct {
    char pad0[0x20];
    int count;
} IKSetup;

typedef struct {
    char pad0[0x31C];
    IKInfo *ik;
    char pad320[0x38];
    IKSetup *setup;
} CharacterClass;

void ResetCharacterClassIKInfo(CharacterClass *chara)
{
    IKSetup *setup = chara->setup;

    if (setup != 0) {
        int n = setup->count;
        IKInfo *ik = chara->ik;

        while (n--) {
            ik->enable = 0;
            ik->unkB0 = 0;
            ik->weight = 1.0f;
            ik->unkB4 = 0;
            ik->active = 0;
            ik->range = 100.0f;
            ik->unkC0 = 0;
            ik++;
        }
    }
}
