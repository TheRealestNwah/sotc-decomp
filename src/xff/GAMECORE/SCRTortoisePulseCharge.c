extern void RequestCharacterMotionShiftFunc(void *, void *);
extern unsigned char D_000CB538[1];

void SCRTortoisePulseCharge(void *character)
{
    RequestCharacterMotionShiftFunc(character, &D_000CB538);
}
