extern void RequestCharacterMotionShiftFunc(void *, void *);
extern unsigned char D_0007D5B0[1];

void SCRItemTakeBegin(void *character)
{
    RequestCharacterMotionShiftFunc(character, &D_0007D5B0);
}
