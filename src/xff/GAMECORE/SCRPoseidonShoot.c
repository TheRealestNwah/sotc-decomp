extern void RequestCharacterMotionShiftFunc(void *character, void (*func)(void *character));
extern void func_000939A0(void *character);

void SCRPoseidonShoot(void *character)
{
    RequestCharacterMotionShiftFunc(character, &func_000939A0);
}
