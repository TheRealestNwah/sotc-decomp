extern void RequestCharacterMotionShiftFunc(void *, void *);
extern unsigned char func_00064678[1];

void SCRLeoDashAttack(void *character)
{
    RequestCharacterMotionShiftFunc(character, &func_00064678);
}
