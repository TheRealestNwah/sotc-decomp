extern void RequestCharacterMotionShiftFunc(void *, void *);
extern unsigned char D_0007D9D8[1];

void SCRPlayerCombatMode(void *character)
{
    RequestCharacterMotionShiftFunc(character, &D_0007D9D8);
}
