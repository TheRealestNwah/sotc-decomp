extern void RequestCharacterMotionShiftFunc(void *character, void (*func)(void *character));
extern void func_0006AA40(void *character);

void SCRCanossaWallBreakEnd(void *character)
{
    RequestCharacterMotionShiftFunc(character, &func_0006AA40);
}
