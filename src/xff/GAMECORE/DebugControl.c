typedef struct { char pad0[0x150]; signed char disabled; } CharacterClass;
extern CharacterClass *GetCharacterClass(void *);
extern void CharaCtrlAIControl(void *, void *, float, float);
extern void CharaCtrlPlayableControl(void *, void *, int, float);
void DebugControl(void *actor, void *target, int input, int ai, float unused, float interval, float weight)
{
    CharacterClass *character = GetCharacterClass(actor);
    if (character != 0 && character->disabled == 0) {
        if (ai != 0)
            CharaCtrlAIControl(actor, target, interval, weight);
        else
            CharaCtrlPlayableControl(actor, target, input, weight);
    }
}
