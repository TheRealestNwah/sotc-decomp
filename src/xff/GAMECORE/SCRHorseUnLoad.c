extern void RequestCharacterMotionShiftFunc(void *character, void (*func)(void *character));
extern void func_0005D2C8(void *character);

void SCRHorseUnLoad(void *character)
{
    RequestCharacterMotionShiftFunc(character, &func_0005D2C8);
}
