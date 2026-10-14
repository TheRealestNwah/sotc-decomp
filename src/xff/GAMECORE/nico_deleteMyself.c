extern void RequestCharacterMotionShiftFunc(void *, void *);
extern unsigned char func_0000B670[1];

void nico_deleteMyself(void *character)
{
    RequestCharacterMotionShiftFunc(character, &func_0000B670);
}
