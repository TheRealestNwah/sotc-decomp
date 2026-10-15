extern void RequestCharacterMotionShiftFunc(void *, void *);
extern unsigned char D_0007DB80[];

void SCRPlayerPauseEnable(void *character)
{
    RequestCharacterMotionShiftFunc(character, D_0007DB80);
}
