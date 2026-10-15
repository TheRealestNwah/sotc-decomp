extern void RequestCharacterMotionShiftFunc(void *character, void (*func)(void *character));
extern void func_00052398(void *character);

void SCRRockFall(void *character)
{
    RequestCharacterMotionShiftFunc(character, &func_00052398);
}
