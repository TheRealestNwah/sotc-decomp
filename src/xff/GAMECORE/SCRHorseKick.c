extern void RequestCharacterMotionShiftFunc(void *, void *);
extern unsigned char D_0007DC40[1];

void SCRHorseKick(void *character)
{
    RequestCharacterMotionShiftFunc(character, &D_0007DC40);
}
