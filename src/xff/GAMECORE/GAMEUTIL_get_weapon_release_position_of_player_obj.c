typedef int s128 __attribute__((mode(TI)));

extern char *GetCharacterClass(void *);
extern char *GetLayoutClass(void *);
extern void GetMotionNodePos(void *, void *, int, int);

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

static inline int is_player(void *actor)
{
    return get_character_type(actor) == 2;
}

int GAMEUTIL_get_weapon_release_position_of_player_obj(void *out, void *actor)
{
    if (is_player(actor)) {
        GetMotionNodePos(out, actor, 0x10000, 0);
        return 1;
    }
    *(s128 *)out = **(s128 **)(GetLayoutClass(actor) + 0x134);
    return 0;
}
