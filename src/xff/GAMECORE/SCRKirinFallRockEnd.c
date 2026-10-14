extern void RequestCharacterMotionShiftFunc(void *, void *);
extern unsigned char func_00062FD8[1];

void SCRKirinFallRockEnd(void *character)
{
    RequestCharacterMotionShiftFunc(character, &func_00062FD8);
}
