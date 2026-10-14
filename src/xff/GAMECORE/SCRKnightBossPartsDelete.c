extern void RequestCharacterMotionShiftFunc(void *, void *);
extern unsigned char func_00063980[1];

void SCRKnightBossPartsDelete(void *character)
{
    RequestCharacterMotionShiftFunc(character, &func_00063980);
}
