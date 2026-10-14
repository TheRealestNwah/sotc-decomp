extern void RequestCharacterMotionShiftFunc(void *, void *);
extern unsigned char func_000CB608[1];

void SCRFallRockSub(void *character)
{
    RequestCharacterMotionShiftFunc(character, &func_000CB608);
}
