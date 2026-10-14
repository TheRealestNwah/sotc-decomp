extern void RequestCharacterMotionShiftFunc(void *, void *);
extern unsigned char D_000CB500[1];

void SCRTortoiseShoot(void *character)
{
    RequestCharacterMotionShiftFunc(character, &D_000CB500);
}
