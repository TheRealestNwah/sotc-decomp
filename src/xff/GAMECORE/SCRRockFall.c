extern void RequestCharacterMotionShiftFunc(void *, void *);
extern unsigned char func_00052398[1];

void SCRRockFall(void *character)
{
    RequestCharacterMotionShiftFunc(character, &func_00052398);
}
