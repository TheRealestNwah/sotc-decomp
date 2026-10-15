extern char *GetCharacterClass(void *);
extern void nico_setHorseBridleRightLong(void *);

static inline void *getHorse(void *a)
{
    void *h = *(void **)(GetCharacterClass(a) + 0x950);
    if (h != a && *(short *)(GetCharacterClass(h) + 0x370) == 3)
        return h;
    return 0;
}

void nico_setPlayerHorseBridleRightLong(void *a)
{
    void *h = getHorse(a);
    if (h != 0)
        nico_setHorseBridleRightLong(h);
}
