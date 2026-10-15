extern void RequestCharacterMotionShiftFunc(void *character, void (*func)(void *character));
extern void D_0007D890(void *character);

void SCRPlayerSendDamage(void *character)
{
    RequestCharacterMotionShiftFunc(character, D_0007D890);
}
