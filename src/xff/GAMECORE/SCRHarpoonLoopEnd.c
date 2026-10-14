extern void RequestCharacterMotionShiftFunc(void *, void *);
extern unsigned char D_0007D708[1];

void SCRHarpoonLoopEnd(void *character)
{
    RequestCharacterMotionShiftFunc(character, &D_0007D708);
}
