extern void RequestCharacterMotionShiftFunc(void *character, void (*func)(void *character));
extern void T_00079BD8(void *character);

void SCRPlayerSendDamageLater(void *character)
{
    RequestCharacterMotionShiftFunc(character, &T_00079BD8);
}
