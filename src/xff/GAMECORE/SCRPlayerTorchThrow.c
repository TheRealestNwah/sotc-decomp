extern void RequestCharacterMotionShiftFunc(void *character, void (*func)(void *character));
extern void T_0007AA48(void *character);

void SCRPlayerTorchThrow(void *character)
{
    RequestCharacterMotionShiftFunc(character, &T_0007AA48);
}
