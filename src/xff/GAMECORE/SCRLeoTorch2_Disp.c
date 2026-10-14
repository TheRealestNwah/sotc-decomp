extern void RequestCharacterMotionShiftFunc(void *, void *);
extern unsigned char D_000644B0[1];

void SCRLeoTorch2_Disp(void *character)
{
    RequestCharacterMotionShiftFunc(character, &D_000644B0);
}
