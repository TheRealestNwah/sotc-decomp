extern void RequestCharacterMotionShiftFunc(void *, void *);
extern unsigned char D_0007D848[];

void SCRPlayerSendDamageStart(void *character)
{
    RequestCharacterMotionShiftFunc(character, D_0007D848);
}
