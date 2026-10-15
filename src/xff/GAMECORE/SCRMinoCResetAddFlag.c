extern void RequestCharacterMotionShiftFunc(void *character, void (*func)(void *character));
extern void func_0006BF08(void *character);

void SCRMinoCResetAddFlag(void *character)
{
    RequestCharacterMotionShiftFunc(character, &func_0006BF08);
}
