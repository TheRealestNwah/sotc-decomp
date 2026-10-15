extern void RequestCharacterMotionShiftFunc(void *character, void (*func)(void *character));
extern void func_000523C0(void *character);

void SCRRockReset(void *character)
{
    RequestCharacterMotionShiftFunc(character, &func_000523C0);
}
