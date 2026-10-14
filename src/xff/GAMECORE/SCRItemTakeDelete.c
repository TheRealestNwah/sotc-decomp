extern void RequestCharacterMotionShiftFunc(void *, void *);
extern unsigned char D_0007D630[1];

void SCRItemTakeDelete(void *character)
{
    RequestCharacterMotionShiftFunc(character, &D_0007D630);
}
