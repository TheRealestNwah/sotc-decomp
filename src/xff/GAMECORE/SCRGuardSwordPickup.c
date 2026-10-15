extern void RequestCharacterMotionShiftFunc(void *character, void (*func)(void *character));
extern void func_00055AE0(void *character);

void SCRGuardSwordPickup(void *character)
{
    RequestCharacterMotionShiftFunc(character, &func_00055AE0);
}
