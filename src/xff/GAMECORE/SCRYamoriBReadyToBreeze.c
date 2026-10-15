extern void RequestCharacterMotionShiftFunc(void *character, void (*func)(void *character));
extern void func_000D15F8(void *character);

void SCRYamoriBReadyToBreeze(void *character)
{
    RequestCharacterMotionShiftFunc(character, &func_000D15F8);
}
