extern void RequestCharacterMotionShiftFunc(void *character, void (*func)(void *character));
extern void D_0007D5E8(void *character);

void SCRItemTakeEnd(void *character)
{
    RequestCharacterMotionShiftFunc(character, D_0007D5E8);
}
