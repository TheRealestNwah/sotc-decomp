extern void RequestCharacterMotionShiftFunc(void *, void *);
extern unsigned char func_00035438[1];

void SCRBirdStopBreath(void *character)
{
    RequestCharacterMotionShiftFunc(character, &func_00035438);
}
