extern void *GetCharacterClass(void *);
int SCRSetCharaRootTurnScaleRatio(void *actor, float ratio)
{
    char *character = GetCharacterClass(actor);
    if (character != 0) {
        *(float *)(character + 0x574) = ratio;
        return 1;
    }
    return 0;
}
