extern void RequestCharacterMotionShiftFunc(void *character, void (*func)(void *character));
extern void D_000361D0(void *character);

void SCRMammothBreaksWall(void *character)
{
    RequestCharacterMotionShiftFunc(character, D_000361D0);
}
