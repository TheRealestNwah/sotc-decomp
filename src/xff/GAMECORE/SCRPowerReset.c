extern void RequestCharacterMotionShiftFunc(void *character, void (*func)(void *character));
extern void func_0001EA48(void *character);

void SCRPowerReset(void *character)
{
    RequestCharacterMotionShiftFunc(character, &func_0001EA48);
}
