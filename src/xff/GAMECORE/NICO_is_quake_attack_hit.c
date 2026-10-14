extern int GAMEUTIL_get_parent_collision_attribute(long *, int);

int NICO_is_quake_attack_hit(int a)
{
    long attr = 0;

    return GAMEUTIL_get_parent_collision_attribute(&attr, a) == 1;
}
