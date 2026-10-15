extern void RequestCharacterMotionShiftFunc(void *character, void (*func)(void *character));
extern void D_00064550(void *character);

void SCRLeoTorch3_Disp(void *character)
{
    RequestCharacterMotionShiftFunc(character, D_00064550);
}
