extern void RequestCharacterMotionShiftFunc(void *character, void (*func)(void *character));
extern void D_000645F0(void *character);

void SCRLeoArmorBroken(void *character)
{
    RequestCharacterMotionShiftFunc(character, D_000645F0);
}
