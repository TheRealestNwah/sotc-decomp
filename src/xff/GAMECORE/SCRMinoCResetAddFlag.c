extern void RequestCharacterMotionShiftFunc(void *, void *);
extern unsigned char func_0006BF08[1];

void SCRMinoCResetAddFlag(void *character)
{
    RequestCharacterMotionShiftFunc(character, &func_0006BF08);
}
