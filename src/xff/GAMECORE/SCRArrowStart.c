extern void RequestCharacterMotionShiftFunc(void *, void *);
extern unsigned char D_0007D648[1];

void SCRArrowStart(void *character)
{
    RequestCharacterMotionShiftFunc(character, &D_0007D648);
}
