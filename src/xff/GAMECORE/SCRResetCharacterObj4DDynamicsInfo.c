extern void RequestCharacterMotionShiftFunc(void *character, void (*func)(void *character));
extern void func_00044888(void *character);

void SCRResetCharacterObj4DDynamicsInfo(void *character)
{
    RequestCharacterMotionShiftFunc(character, &func_00044888);
}
