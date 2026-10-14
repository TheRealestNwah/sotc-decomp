extern void RequestCharacterMotionShiftFunc(void *, void *);
extern unsigned char D_0007DA20[1];

void SCRPlayerNonCombatMode(void *character)
{
    RequestCharacterMotionShiftFunc(character, &D_0007DA20);
}
