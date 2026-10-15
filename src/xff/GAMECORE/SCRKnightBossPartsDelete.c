extern void RequestCharacterMotionShiftFunc(void *character, void (*func)(void *character));
extern void func_00063980(void *character);

void SCRKnightBossPartsDelete(void *character)
{
    RequestCharacterMotionShiftFunc(character, &func_00063980);
}
