extern void RequestCharacterMotionShiftFunc(void *character, void (*func)(void *character));
extern void func_0006BED0(void *character);

void SCRMinoCSetAddFlag(void *character)
{
    RequestCharacterMotionShiftFunc(character, &func_0006BED0);
}
