extern void RequestCharacterMotionShiftFunc(void *, void *);
extern unsigned char func_00035408[1];

void SCRBirdStartBreath(void *character)
{
    RequestCharacterMotionShiftFunc(character, &func_00035408);
}
