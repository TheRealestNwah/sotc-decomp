extern int GetParentCharColAttr(long *, char *);
int GAMEUTIL_get_parent_collision_attribute(long *out, char *object)
{
    return GetParentCharColAttr(out, object);
}
