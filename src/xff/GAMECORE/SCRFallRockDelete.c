extern void RequestCharacterMotionShiftFunc(void *, void *);
extern unsigned char D_000CB5B8[1];

void SCRFallRockDelete(void *character)
{
    RequestCharacterMotionShiftFunc(character, &D_000CB5B8);
}
