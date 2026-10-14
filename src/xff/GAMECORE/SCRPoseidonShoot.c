extern void RequestCharacterMotionShiftFunc(void *, void *);
extern unsigned char func_000939A0[1];

void SCRPoseidonShoot(void *character)
{
    RequestCharacterMotionShiftFunc(character, &func_000939A0);
}
