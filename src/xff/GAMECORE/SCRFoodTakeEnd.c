extern void RequestCharacterMotionShiftFunc(void *character, void (*func)(void *character));
extern void T_00078DA0(void *character);

void SCRFoodTakeEnd(void *character)
{
    RequestCharacterMotionShiftFunc(character, &T_00078DA0);
}
