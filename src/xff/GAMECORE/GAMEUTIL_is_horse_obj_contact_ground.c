extern char *GetCharacterClass(void *);

static inline void *ridingHorse(void *obj)
{
    char *c = GetCharacterClass(obj);

    if (c != 0) {
        void *h = *(void **)(c + 0x950);

        if (obj != h)
            return h;
    }
    return 0;
}

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

static inline int isHorse(void *actor)
{
    return get_character_type(actor) == 3;
}
int GAMEUTIL_is_horse_obj_contact_ground(void **output, void *actor)
{
    int result = 0;
    void *horse = ridingHorse(actor);
    if (horse != 0) {
        result = 1;
    } else if (isHorse(actor)) {
        horse = actor;
        result = 1;
    }
    if (output != 0)
        *output = horse;
    return result;
}
