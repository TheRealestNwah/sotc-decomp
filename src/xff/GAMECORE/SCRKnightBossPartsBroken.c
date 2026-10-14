extern void RequestCharacterMotionShiftFunc(void *, void *);
extern unsigned char func_000631A0[1];

void SCRKnightBossPartsBroken(void *character)
{
    RequestCharacterMotionShiftFunc(character, &func_000631A0);
}
