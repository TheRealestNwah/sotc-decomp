extern void RequestCharacterMotionShiftFunc(void *, void *);
extern unsigned char T_00079AA8[1];

void SCRHarpoonLoopStart(void *character)
{
    RequestCharacterMotionShiftFunc(character, &T_00079AA8);
}
