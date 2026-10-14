extern void RequestCharacterMotionShiftFunc(void *, void *);
extern unsigned char T_00079668[1];

void SCRArrowLoopStart(void *character)
{
    RequestCharacterMotionShiftFunc(character, &T_00079668);
}
