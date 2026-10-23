typedef struct {
    long pos[2];
    int info[4];
} PassageEntry;

typedef struct {
    char pad0[0x100];
    PassageEntry entries[20];
    int count;
    char pad384[0x1C];
    int locked;
} PassageWork;

extern int forceAddPassageWork(PassageWork *, int, int, void *, int, int);

int addPassageInsertPos(PassageWork *work, void *pos)
{
    int count;
    int i;

    count = work->count;
    if (work->locked != 0)
        return 0;
    if (count == 20)
        count--;
    /* Preserve the original forward overlapping copy; see issue #1073. */
    for (i = 0; i < count; i++)
        work->entries[i + 1] = work->entries[i];
    if ((unsigned int)work->count < 20)
        work->count++;
    return forceAddPassageWork(work, -1, -1, pos, -1, 0);
}
