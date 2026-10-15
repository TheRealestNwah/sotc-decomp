extern void RequestCharacterMotionShiftFunc(void *character, void (*func)(void *character));
extern void func_00064370(void *character);

void SCRLeoTorch0_Disp(void *character)
{
    RequestCharacterMotionShiftFunc(character, &func_00064370);
}
