extern void RequestCharacterMotionShiftFunc(void *, void *);
extern unsigned char D_0007D870[1];

void SCRPlayerSendDamageEnd(void *character)
{
    RequestCharacterMotionShiftFunc(character, &D_0007D870);
}
