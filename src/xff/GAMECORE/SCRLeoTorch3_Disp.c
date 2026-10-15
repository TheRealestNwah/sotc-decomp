extern void RequestCharacterMotionShiftFunc(void *, void *);
extern unsigned char D_00064550[];

void SCRLeoTorch3_Disp(void *character)
{
    RequestCharacterMotionShiftFunc(character, D_00064550);
}
