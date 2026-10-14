extern void RequestCharacterMotionShiftFunc(void *, void *);
extern unsigned char func_0007D588[1];

void SCRFoodTakeBegin(void *character)
{
    RequestCharacterMotionShiftFunc(character, &func_0007D588);
}
