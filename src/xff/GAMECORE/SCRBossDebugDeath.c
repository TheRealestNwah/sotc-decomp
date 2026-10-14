extern void RequestCharacterMotionShiftFunc(void *, void *);
extern unsigned char func_00036190[1];

void SCRBossDebugDeath(void *character)
{
    RequestCharacterMotionShiftFunc(character, &func_00036190);
}
