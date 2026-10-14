extern void RequestCharacterMotionShiftFunc(void *, void *);
extern unsigned char func_000D3CB0[1];

void SCRYamoriBReadyToBreeze2(void *character)
{
    RequestCharacterMotionShiftFunc(character, &func_000D3CB0);
}
