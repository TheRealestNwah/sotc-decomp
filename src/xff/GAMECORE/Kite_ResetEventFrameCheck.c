void Kite_ResetEventFrameCheck(char *p)
{
    *(int *)(p + 0x8) = 0;
    *(int *)(p + 0xC) = 0;
}
