extern void RequestCharacterMotionShiftFunc(void *character, void (*func)(void *character));
extern void D_0007DC40(void *character);

void SCRHorseKick(void *character)
{
    RequestCharacterMotionShiftFunc(character, D_0007DC40);
}
