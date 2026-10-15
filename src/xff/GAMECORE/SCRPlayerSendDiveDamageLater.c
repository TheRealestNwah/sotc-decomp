extern void RequestCharacterMotionShiftFunc(void *character, void (*func)(void *character));
extern void T_00079CA0(void *character);

void SCRPlayerSendDiveDamageLater(void *character)
{
    RequestCharacterMotionShiftFunc(character, &T_00079CA0);
}
