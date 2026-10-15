extern void RequestCharacterMotionShiftFunc(void *character, void (*func)(void *character));
extern void D_000CB538(void *character);

void SCRTortoisePulseCharge(void *character)
{
    RequestCharacterMotionShiftFunc(character, D_000CB538);
}
