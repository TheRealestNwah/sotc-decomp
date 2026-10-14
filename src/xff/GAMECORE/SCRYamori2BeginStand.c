extern void RequestCharacterMotionShiftFunc(void *, void *);
extern unsigned char func_000D3CA8[1];

void SCRYamori2BeginStand(void *character)
{
    RequestCharacterMotionShiftFunc(character, &func_000D3CA8);
}
