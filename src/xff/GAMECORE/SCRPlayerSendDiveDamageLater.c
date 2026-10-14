extern void RequestCharacterMotionShiftFunc(void *, void *);
extern unsigned char T_00079CA0[1];

void SCRPlayerSendDiveDamageLater(void *character)
{
    RequestCharacterMotionShiftFunc(character, &T_00079CA0);
}
