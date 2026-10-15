extern void RequestCharacterMotionShiftFunc(void *character, void (*func)(void *character));
extern void func_00062FD8(void *character);

void SCRKirinFallRockEnd(void *character)
{
    RequestCharacterMotionShiftFunc(character, &func_00062FD8);
}
