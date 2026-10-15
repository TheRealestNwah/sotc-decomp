extern void *GetCharacterClass(void *character);

static inline int checkClothSurface(char *characterClass, float limit)
{
    int result = 1;

    if (*(signed char *)(characterClass + 0x362)) {
        if (*(float *)(characterClass + 0x10C4) > limit) {
            return 0;
        }
        return result;
    }
    return 1;
}

int nico_horseClothOverSurfDetectFunc(void *character)
{
    return checkClothSurface(GetCharacterClass(character), 1.2f);
}

int nico_playerClothOverSurfDetectFunc(void *character)
{
    return checkClothSurface(GetCharacterClass(character), 0.8f);
}
