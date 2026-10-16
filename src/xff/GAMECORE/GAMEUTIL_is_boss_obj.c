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

extern void *GAMEUTIL_get_parent_object(void *);

static inline int is_boss(void *actor)
{
    return get_character_type(actor) == 4;
}

/* Reading p through a pointer (found by the permuter) keeps the inlined null
   check inside the loop, as in the original. */
int GAMEUTIL_is_boss_obj(void *actor, int parents)
{
    void *p;

    if (parents == 0)
        return is_boss(actor);
    for (p = actor; p != 0; p = GAMEUTIL_get_parent_object(p)) {
        void **pp = &p;

        if (get_character_type(*pp) == 4)
            return 1;
    }
    return 0;
}
