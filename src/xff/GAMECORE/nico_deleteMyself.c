extern void RequestCharacterMotionShiftFunc(void *character, void (*func)(void *character));
extern void func_0000B670(void *character);

void nico_deleteMyself(void *character)
{
    RequestCharacterMotionShiftFunc(character, &func_0000B670);
}
