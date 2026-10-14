extern void RequestCharacterMotionShiftFunc(void *, void *);
extern unsigned char func_00041960[1];

void SCRCerberusPollFalldown(void *character)
{
    RequestCharacterMotionShiftFunc(character, &func_00041960);
}
