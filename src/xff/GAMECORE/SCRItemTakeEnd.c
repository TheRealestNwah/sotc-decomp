extern void RequestCharacterMotionShiftFunc(void *, void *);
extern unsigned char D_0007D5E8[1];

void SCRItemTakeEnd(void *character)
{
    RequestCharacterMotionShiftFunc(character, &D_0007D5E8);
}
