extern void RequestCharacterMotionShiftFunc(void *character, void (*func)(void *character));
extern void D_000644B0(void *character);

void SCRLeoTorch2_Disp(void *character)
{
    RequestCharacterMotionShiftFunc(character, D_000644B0);
}
