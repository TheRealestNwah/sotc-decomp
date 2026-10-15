extern void RequestCharacterMotionShiftFunc(void *character, void (*func)(void *character));
extern void func_0006AA88(void *character);

void SCRCanossaWallDelete(void *character)
{
    RequestCharacterMotionShiftFunc(character, &func_0006AA88);
}
