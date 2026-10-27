extern int GAMEUTIL_get_parent_collision_attribute(long *, char *);
static inline long bossFlag(const long *attribute)
{
    return *attribute & 1L;
}
int GAMEUTIL_is_parent_collision_attribute_boss(char *actor)
{
    long attr[2];
    int result = GAMEUTIL_get_parent_collision_attribute(attr, actor);
    if (result == 1) {
        if (bossFlag(attr)) {
            return result;
        }
    }
    return 0;
}