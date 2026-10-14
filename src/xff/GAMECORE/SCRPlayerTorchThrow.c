extern void RequestCharacterMotionShiftFunc(void *, void *);
extern unsigned char T_0007AA48[1];

void SCRPlayerTorchThrow(void *character)
{
    RequestCharacterMotionShiftFunc(character, &T_0007AA48);
}
