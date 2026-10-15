extern void RequestCharacterMotionShiftFunc(void *, void *);
extern unsigned char D_0007D6A8[];

void SCRHarpoonStart(void *character)
{
    RequestCharacterMotionShiftFunc(character, D_0007D6A8);
}
