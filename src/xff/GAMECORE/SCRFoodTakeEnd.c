extern void RequestCharacterMotionShiftFunc(void *, void *);
extern unsigned char T_00078DA0[1];

void SCRFoodTakeEnd(void *character)
{
    RequestCharacterMotionShiftFunc(character, &T_00078DA0);
}
