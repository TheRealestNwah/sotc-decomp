extern void RequestCharacterMotionShiftFunc(void *, void *);
extern unsigned char func_0001EA48[1];

void SCRPowerReset(void *character)
{
    RequestCharacterMotionShiftFunc(character, &func_0001EA48);
}
