extern void RequestCharacterMotionShiftFunc(void *character, void (*func)(void *character));
extern void func_000CB608(void *character);

void SCRFallRockSub(void *character)
{
    RequestCharacterMotionShiftFunc(character, &func_000CB608);
}
