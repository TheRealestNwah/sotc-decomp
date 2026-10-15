extern void RequestCharacterMotionShiftFunc(void *character, void (*func)(void *character));
extern void func_0003FAD0(void *character);

void SCRBuddhaShoot(void *character)
{
    RequestCharacterMotionShiftFunc(character, &func_0003FAD0);
}
