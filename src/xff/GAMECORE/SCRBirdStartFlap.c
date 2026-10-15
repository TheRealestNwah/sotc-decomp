extern void RequestCharacterMotionShiftFunc(void *, void *);
extern unsigned char D_00035468[];

void SCRBirdStartFlap(void *character)
{
    RequestCharacterMotionShiftFunc(character, D_00035468);
}
