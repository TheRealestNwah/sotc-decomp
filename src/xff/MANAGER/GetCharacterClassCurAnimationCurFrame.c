float GetCharacterClassCurAnimationCurFrame(int arg0)
{
    void *temp_a0;

    temp_a0 = arg0 + 0x1C0;
    return (*(float *)((char *)(temp_a0) + 8)) * (*(float *)((char *)(temp_a0) + 0x2C));
}
