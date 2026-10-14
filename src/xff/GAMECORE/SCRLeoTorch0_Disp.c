extern void RequestCharacterMotionShiftFunc(void *, void *);
extern unsigned char func_00064370[1];

void SCRLeoTorch0_Disp(void *character)
{
    RequestCharacterMotionShiftFunc(character, &func_00064370);
}
