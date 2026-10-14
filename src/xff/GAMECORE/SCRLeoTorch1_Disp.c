extern void RequestCharacterMotionShiftFunc(void *, void *);
extern unsigned char D_00064410[1];

void SCRLeoTorch1_Disp(void *character)
{
    RequestCharacterMotionShiftFunc(character, &D_00064410);
}
