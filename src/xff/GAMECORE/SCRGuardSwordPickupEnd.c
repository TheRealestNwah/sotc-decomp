extern void RequestCharacterMotionShiftFunc(void *character, void (*func)(void *character));
extern void func_00055B48(void *character);

void SCRGuardSwordPickupEnd(void *character)
{
    RequestCharacterMotionShiftFunc(character, &func_00055B48);
}
