extern char *GetCharacterClass();

int SCRSetCharaRootTurnScaleRatio(int a, float r)
{
    char *c = GetCharacterClass(a);

    if (c != 0) {
        *(float *)(c + 0x574) = r;
        return 1;
    }
    return 0;
}
