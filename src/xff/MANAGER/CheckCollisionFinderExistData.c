typedef struct {
    int f0;
    int id;
} FinderEntry;

typedef struct {
    int max;
    int count;
    int pad8;
    FinderEntry *entries;
} CollisionFinder;

int CheckCollisionFinderExistData(CollisionFinder *finder, int start, int id)
{
    int i;
    int count = finder->count;
    int n = finder->max;
    FinderEntry *e;

    if (count < n) {
        n = count;
    }
    e = &finder->entries[start];
    for (i = start; i < n; i++, e++) {
        if ((e->id & 0xFFFFFF) == id) {
            return 1;
        }
    }
    return 0;
}
