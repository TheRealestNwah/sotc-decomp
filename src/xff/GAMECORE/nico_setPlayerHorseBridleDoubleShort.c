extern char *GetCharacterClass(void *);
extern void nico_setHorseBridleDoubleShort(void *);

static inline void *getHorse(void *a)
{
    void *h = *(void **)(GetCharacterClass(a) + 0x950);
    if (h != a && *(short *)(GetCharacterClass(h) + 0x370) == 3)
        return h;
    return 0;
}

void nico_setPlayerHorseBridleDoubleShort(void *a)
{
    void *h = getHorse(a);
    if (h != 0)
        nico_setHorseBridleDoubleShort(h);
}
