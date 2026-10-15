extern char *GetCharacterClass(void *);

static inline int get_character_type(void *actor)
{
    char *c;
    if (actor != 0) {
        c = GetCharacterClass(actor);
        if (c != 0)
            return *(short *)(c + 0x370);
    }
    return -1000000;
}

int GAMEUTIL_is_player_obj(void *actor)
{
    return get_character_type(actor) == 2;
}
