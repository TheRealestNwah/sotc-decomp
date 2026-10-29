extern int *DldSysUndefSymbol;
typedef struct {
    unsigned int *frames;
    void *frameData;
    unsigned int *entries;
    void *entryData;
} AnimeFrameTable;
static inline char *resolveNullable(unsigned int *h)
{
    if (h != 0) {
        unsigned int v = *h;
        int off = v & 0x3FFFF;
        int *t = off != 0 ? *(int **)((char *)h - off) : 0;
        return t != 0 && t != DldSysUndefSymbol ? (char *)t[4] + ((v >> 18) & 0xFFF) * ((int *)t[2])[3] : 0;
    }
    return 0;
}
void ResetAnimeFrameTableInfo(AnimeFrameTable *table, unsigned int *frames, unsigned int *entries)
{
    table->frames = frames;
    table->frameData = resolveNullable(frames);
    table->entries = entries;
    table->entryData = resolveNullable(entries);
}
