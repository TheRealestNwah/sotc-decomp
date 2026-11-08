typedef struct { int id; int size; } FileEnt;
extern FileEnt B_000543A8[];

static inline FileEnt *findFile(int id)
{
    int i;
    for (i = 0; i < 8; i++) {
        if (B_000543A8[i].id == id)
            return &B_000543A8[i];
    }
    return 0;
}

/* Parked: 4 words differ; the original has a single exit with v0=0 in the delay slot, this has two jr. */
#ifdef NONMATCHING
int iosLoaderGetFileSize(int id)
{
    FileEnt *e = findFile(id);
    return e ? e->size : 0;
}
#else
extern int iosLoaderGetFileSize(int id);
#endif
