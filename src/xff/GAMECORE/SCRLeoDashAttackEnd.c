extern void RequestCharacterMotionShiftFunc(void *character, void (*func)(void *character));
extern void func_00064670(void *character);

void SCRLeoDashAttackEnd(void *character)
{
    RequestCharacterMotionShiftFunc(character, &func_00064670);
}
