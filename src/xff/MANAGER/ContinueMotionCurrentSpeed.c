extern char *GetCharacterClass(int);

void ContinueMotionCurrentSpeed(int a)
{
    char *c = GetCharacterClass(a);
    char *m = c + 0x1C0;
    float v = *(float *)(c + 0x5C0);
    if (*(signed char *)(c + 0x5E2) != 0) {
        *(float *)(m + 0x1C) = v;
    }
}
