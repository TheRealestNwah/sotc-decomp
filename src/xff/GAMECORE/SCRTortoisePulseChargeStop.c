extern void RequestCharacterMotionShiftFunc(void *character, void (*func)(void *character));
extern void D_000CB598(void *character);

void SCRTortoisePulseChargeStop(void *character)
{
    RequestCharacterMotionShiftFunc(character, D_000CB598);
}
