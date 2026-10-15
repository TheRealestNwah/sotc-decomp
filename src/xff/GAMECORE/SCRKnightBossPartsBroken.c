extern void RequestCharacterMotionShiftFunc(void *character, void (*func)(void *character));
extern void func_000631A0(void *character);

void SCRKnightBossPartsBroken(void *character)
{
    RequestCharacterMotionShiftFunc(character, &func_000631A0);
}
