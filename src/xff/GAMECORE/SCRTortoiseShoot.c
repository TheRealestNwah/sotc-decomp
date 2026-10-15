extern void RequestCharacterMotionShiftFunc(void *character, void (*func)(void *character));
extern void D_000CB500(void *character);

void SCRTortoiseShoot(void *character)
{
    RequestCharacterMotionShiftFunc(character, D_000CB500);
}
