extern void RequestCharacterMotionShiftFunc(void *, void *);
extern unsigned char T_00079800[1];

void SCRArrowLoopEnd(void *character)
{
    RequestCharacterMotionShiftFunc(character, &T_00079800);
}
