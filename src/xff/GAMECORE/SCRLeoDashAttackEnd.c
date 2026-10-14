extern void RequestCharacterMotionShiftFunc(void *, void *);
extern unsigned char func_00064670[1];

void SCRLeoDashAttackEnd(void *character)
{
    RequestCharacterMotionShiftFunc(character, &func_00064670);
}
