extern void RequestCharacterMotionShiftFunc(void *, void *);
extern unsigned char D_0007DB60[1];

void SCRPlayerPauseDisable(void *character)
{
    RequestCharacterMotionShiftFunc(character, &D_0007DB60);
}
