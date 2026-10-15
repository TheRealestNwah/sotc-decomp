extern void RequestCharacterMotionShiftFunc(void *character, void (*func)(void *character));
extern void D_0007D5B0(void *character);

void SCRItemTakeBegin(void *character)
{
    RequestCharacterMotionShiftFunc(character, D_0007D5B0);
}
