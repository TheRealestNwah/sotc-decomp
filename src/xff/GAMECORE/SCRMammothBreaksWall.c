extern void RequestCharacterMotionShiftFunc(void *, void *);
extern unsigned char D_000361D0[];

void SCRMammothBreaksWall(void *character)
{
    RequestCharacterMotionShiftFunc(character, D_000361D0);
}
