extern void RequestCharacterMotionShiftFunc(void *character, void (*func)(void *character));
extern void func_0007D588(void *character);

void SCRFoodTakeBegin(void *character)
{
    RequestCharacterMotionShiftFunc(character, &func_0007D588);
}
