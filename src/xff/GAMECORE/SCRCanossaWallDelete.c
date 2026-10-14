extern void RequestCharacterMotionShiftFunc(void *, void *);
extern unsigned char func_0006AA88[1];

void SCRCanossaWallDelete(void *character)
{
    RequestCharacterMotionShiftFunc(character, &func_0006AA88);
}
