extern void RequestCharacterMotionShiftFunc(void *, void *);
extern unsigned char func_0006AA40[1];

void SCRCanossaWallBreakEnd(void *character)
{
    RequestCharacterMotionShiftFunc(character, &func_0006AA40);
}
