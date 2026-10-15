extern int GAMEUTIL_get_parent_collision_attribute(long *, void *);

int NICO_is_quake_attack_hit_except_boss(void *actor)
{
    long attr[2];
    attr[0] = 0;
    if (GAMEUTIL_get_parent_collision_attribute(attr, actor) == 1 && !(attr[0] & 1))
        return 1;
    return 0;
}
