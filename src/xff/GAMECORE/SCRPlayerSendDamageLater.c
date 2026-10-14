extern void RequestCharacterMotionShiftFunc(void *, void *);
extern unsigned char T_00079BD8[1];

void SCRPlayerSendDamageLater(void *character)
{
    RequestCharacterMotionShiftFunc(character, &T_00079BD8);
}
