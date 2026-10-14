extern void RequestCharacterMotionShiftFunc(void *, void *);
extern unsigned char func_0006BED0[1];

void SCRMinoCSetAddFlag(void *character)
{
    RequestCharacterMotionShiftFunc(character, &func_0006BED0);
}
