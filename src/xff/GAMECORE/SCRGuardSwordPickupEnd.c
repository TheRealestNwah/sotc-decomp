extern void RequestCharacterMotionShiftFunc(void *, void *);
extern unsigned char func_00055B48[1];

void SCRGuardSwordPickupEnd(void *character)
{
    RequestCharacterMotionShiftFunc(character, &func_00055B48);
}
