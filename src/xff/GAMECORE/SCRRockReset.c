extern void RequestCharacterMotionShiftFunc(void *, void *);
extern unsigned char func_000523C0[1];

void SCRRockReset(void *character)
{
    RequestCharacterMotionShiftFunc(character, &func_000523C0);
}
