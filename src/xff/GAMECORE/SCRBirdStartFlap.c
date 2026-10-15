extern void RequestCharacterMotionShiftFunc(void *character, void (*func)(void *character));
extern void D_00035468(void *character);

void SCRBirdStartFlap(void *character)
{
    RequestCharacterMotionShiftFunc(character, D_00035468);
}
