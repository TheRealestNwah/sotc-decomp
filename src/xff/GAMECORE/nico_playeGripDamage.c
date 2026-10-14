extern void RequestCharacterMotionShiftFunc(void *, void *);
extern unsigned char func_0007DCB0[1];

void nico_playeGripDamage(void *character)
{
    RequestCharacterMotionShiftFunc(character, &func_0007DCB0);
}
