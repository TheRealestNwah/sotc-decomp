extern void RequestCharacterMotionShiftFunc(void *character, void (*func)(void *character));
extern void func_000D3CA8(void *character);

void SCRYamori2BeginStand(void *character)
{
    RequestCharacterMotionShiftFunc(character, &func_000D3CA8);
}
