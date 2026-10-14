extern void RequestCharacterMotionShiftFunc(void *, void *);
extern unsigned char func_0005D2C8[1];

void SCRHorseUnLoad(void *character)
{
    RequestCharacterMotionShiftFunc(character, &func_0005D2C8);
}
