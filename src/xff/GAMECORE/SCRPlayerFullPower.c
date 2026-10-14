extern void RequestCharacterMotionShiftFunc(void *, void *);
extern unsigned char D_0007D998[1];

void SCRPlayerFullPower(void *character)
{
    RequestCharacterMotionShiftFunc(character, &D_0007D998);
}
