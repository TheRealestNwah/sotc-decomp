extern void RequestCharacterMotionShiftFunc(void *character, void (*func)(void *character));
extern void func_00036190(void *character);

void SCRBossDebugDeath(void *character)
{
    RequestCharacterMotionShiftFunc(character, &func_00036190);
}
