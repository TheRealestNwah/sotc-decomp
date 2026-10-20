extern void *GetCharacterClass(void *);
int nico_playerCheckNippingWithHorseAndWall(int actor)
{
    char *player = GetCharacterClass((void *)actor);
    if (*(signed char *)(player + 0x535) && *(int *)(player + 0xFF0)) {
        int horse = *(int *)(player + 0xFF8);
        char *character = GetCharacterClass((void *)horse);
        if (character && *(short *)(character + 0x370) == 3)
            return horse;
    }
    return 0;
}
