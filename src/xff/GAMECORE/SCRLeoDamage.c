extern void RequestCharacterMotionShiftFunc(void *character, void (*func)(void *character));
extern void func_00064668(void *character);

void SCRLeoDamage(void *character)
{
    RequestCharacterMotionShiftFunc(character, &func_00064668);
}
