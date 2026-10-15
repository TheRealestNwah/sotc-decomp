extern void RequestCharacterMotionShiftFunc(void *character, void (*func)(void *character));
extern void func_0006BE58(void *character);

void SCRMinotourCFallWeapon(void *character)
{
    RequestCharacterMotionShiftFunc(character, &func_0006BE58);
}
