extern void RequestCharacterMotionShiftFunc(void *, void *);
extern unsigned char func_00064668[1];

void SCRLeoDamage(void *character)
{
    RequestCharacterMotionShiftFunc(character, &func_00064668);
}
