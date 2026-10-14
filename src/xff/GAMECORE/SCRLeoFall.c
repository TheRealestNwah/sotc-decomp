extern void RequestCharacterMotionShiftFunc(void *, void *);
extern unsigned char func_00064660[1];

void SCRLeoFall(void *character)
{
    RequestCharacterMotionShiftFunc(character, &func_00064660);
}
