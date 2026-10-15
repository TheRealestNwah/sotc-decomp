extern void RequestCharacterMotionShiftFunc(void *character, void (*func)(void *character));
extern void D_000CB5B8(void *character);

void SCRFallRockDelete(void *character)
{
    RequestCharacterMotionShiftFunc(character, D_000CB5B8);
}
