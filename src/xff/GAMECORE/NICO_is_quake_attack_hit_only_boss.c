extern int GAMEUTIL_get_parent_collision_attribute(long *, char *);

static inline int is_except_boss(void *actor)
{
    long attr[2];
    attr[0] = 0;
    if (GAMEUTIL_get_parent_collision_attribute(attr, actor) == 1 && !(attr[0] & 1))
        return 1;
    return 0;
}

int NICO_is_quake_attack_hit_only_boss(void *actor)
{
    return is_except_boss(actor) ^ 1;
}
