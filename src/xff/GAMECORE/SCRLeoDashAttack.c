extern void RequestCharacterMotionShiftFunc(void *character, void (*func)(void *character));
extern void func_00064678(void *character);

void SCRLeoDashAttack(void *character)
{
    RequestCharacterMotionShiftFunc(character, &func_00064678);
}
