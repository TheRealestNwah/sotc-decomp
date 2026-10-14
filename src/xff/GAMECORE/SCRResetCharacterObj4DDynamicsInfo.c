extern void RequestCharacterMotionShiftFunc(void *, void *);
extern unsigned char func_00044888[1];

void SCRResetCharacterObj4DDynamicsInfo(void *character)
{
    RequestCharacterMotionShiftFunc(character, &func_00044888);
}
