extern char *GetCharacterClass(void *);

void *GAMEUTIL_get_riding_horse_object(void *obj)
{
    char *c = GetCharacterClass(obj);

    if (c != 0) {
        void *h = *(void **)(c + 0x950);

        if (obj != h)
            return h;
    }
    return 0;
}
