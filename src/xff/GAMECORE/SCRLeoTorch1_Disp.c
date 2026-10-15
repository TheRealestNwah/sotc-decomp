extern void RequestCharacterMotionShiftFunc(void *character, void (*func)(void *character));
extern void D_00064410(void *character);

void SCRLeoTorch1_Disp(void *character)
{
    RequestCharacterMotionShiftFunc(character, D_00064410);
}
