extern void *GetCharacterClass(void *obj);

int GAMEUTIL_get_motion_kind(void *obj)
{
    char *c = GetCharacterClass(obj);

    if (c != 0) {
        return *(int *)(c + 0x578);
    }
    return (int)c;
}
