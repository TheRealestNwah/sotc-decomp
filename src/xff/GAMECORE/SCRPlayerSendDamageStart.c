extern void RequestCharacterMotionShiftFunc(void *character, void (*func)(void *character));
extern void D_0007D848(void *character);

void SCRPlayerSendDamageStart(void *character)
{
    RequestCharacterMotionShiftFunc(character, D_0007D848);
}
