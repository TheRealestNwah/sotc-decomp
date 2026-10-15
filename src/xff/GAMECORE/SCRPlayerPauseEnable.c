extern void RequestCharacterMotionShiftFunc(void *character, void (*func)(void *character));
extern void D_0007DB80(void *character);

void SCRPlayerPauseEnable(void *character)
{
    RequestCharacterMotionShiftFunc(character, D_0007DB80);
}
