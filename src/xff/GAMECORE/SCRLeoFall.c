extern void RequestCharacterMotionShiftFunc(void *character, void (*func)(void *character));
extern void func_00064660(void *character);

void SCRLeoFall(void *character)
{
    RequestCharacterMotionShiftFunc(character, &func_00064660);
}
