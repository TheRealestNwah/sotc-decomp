extern void RequestCharacterMotionShiftFunc(void *character, void (*func)(void *character));
extern void func_00035408(void *character);

void SCRBirdStartBreath(void *character)
{
    RequestCharacterMotionShiftFunc(character, &func_00035408);
}
