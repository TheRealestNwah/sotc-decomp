extern char *GetCharacterClass(void *);

void SetMotionMaximumSpeed(void *actor)
{
    char *c = GetCharacterClass(actor);
    char *m = c + 0x1C0;
    float v = *(float *)(c + 0x5C4) - 0.01f;
    if (*(signed char *)(c + 0x5E2) != 0)
        *(float *)(m + 0x1C) = v;
}
