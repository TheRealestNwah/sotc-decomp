extern void RequestCharacterMotionShiftFunc(void *character, void (*func)(void *character));
extern void func_0007DCB0(void *character);

void nico_playeGripDamage(void *character)
{
    RequestCharacterMotionShiftFunc(character, &func_0007DCB0);
}
