extern void RequestCharacterMotionShiftFunc(void *, void *);
extern unsigned char D_0007DB80[1];

void SCRPlayerPauseEnable(void *character)
{
    RequestCharacterMotionShiftFunc(character, &D_0007DB80);
}
