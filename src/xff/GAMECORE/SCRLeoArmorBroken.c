extern void RequestCharacterMotionShiftFunc(void *, void *);
extern unsigned char D_000645F0[];

void SCRLeoArmorBroken(void *character)
{
    RequestCharacterMotionShiftFunc(character, D_000645F0);
}
