extern void RequestCharacterMotionShiftFunc(void *, void *);
extern unsigned char func_0006BE58[1];

void SCRMinotourCFallWeapon(void *character)
{
    RequestCharacterMotionShiftFunc(character, &func_0006BE58);
}
