extern void RequestCharacterMotionShiftFunc(void *, void *);
extern unsigned char D_000CB598[];

void SCRTortoisePulseChargeStop(void *character)
{
    RequestCharacterMotionShiftFunc(character, D_000CB598);
}
