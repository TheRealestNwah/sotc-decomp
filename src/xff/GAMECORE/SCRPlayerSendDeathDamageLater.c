extern void RequestCharacterMotionShiftFunc(void *character, void (*func)(void *character));
extern void D_0007D900(void *character);

void SCRPlayerSendDeathDamageLater(void *character)
{
    RequestCharacterMotionShiftFunc(character, D_0007D900);
}
