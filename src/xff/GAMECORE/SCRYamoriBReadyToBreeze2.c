extern void RequestCharacterMotionShiftFunc(void *character, void (*func)(void *character));
extern void func_000D3CB0(void *character);

void SCRYamoriBReadyToBreeze2(void *character)
{
    RequestCharacterMotionShiftFunc(character, &func_000D3CB0);
}
