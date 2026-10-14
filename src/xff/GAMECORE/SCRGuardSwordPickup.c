extern void RequestCharacterMotionShiftFunc(void *, void *);
extern unsigned char func_00055AE0[1];

void SCRGuardSwordPickup(void *character)
{
    RequestCharacterMotionShiftFunc(character, &func_00055AE0);
}
