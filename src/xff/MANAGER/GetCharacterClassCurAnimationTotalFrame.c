extern int GetMotionResourceFrames(void *);

int GetCharacterClassCurAnimationTotalFrame(char *c)
{
    char *a = c + 0x1C0;
    if (*(char **)a != 0)
        return GetMotionResourceFrames(*(char **)a + 0x50) * *(float *)(a + 0x2C);
    return 0;
}
