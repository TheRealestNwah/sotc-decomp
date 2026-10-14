extern void RequestCharacterMotionShiftFunc(void *, void *);
extern unsigned char func_000D15F8[1];

void SCRYamoriBReadyToBreeze(void *character)
{
    RequestCharacterMotionShiftFunc(character, &func_000D15F8);
}
