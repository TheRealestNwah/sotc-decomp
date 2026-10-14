extern void RequestCharacterMotionShiftFunc(void *, void *);
extern unsigned char D_0007D900[1];

void SCRPlayerSendDeathDamageLater(void *character)
{
    RequestCharacterMotionShiftFunc(character, &D_0007D900);
}
