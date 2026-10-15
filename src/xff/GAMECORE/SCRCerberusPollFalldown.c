extern void RequestCharacterMotionShiftFunc(void *character, void (*func)(void *character));
extern void func_00041960(void *character);

void SCRCerberusPollFalldown(void *character)
{
    RequestCharacterMotionShiftFunc(character, &func_00041960);
}
