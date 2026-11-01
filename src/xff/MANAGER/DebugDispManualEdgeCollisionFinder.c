typedef struct { int p0; int p4; } EdgeDBEntry;
typedef struct { int p0; int p4; int p8; EdgeDBEntry *entries; } EdgeFinder;
extern void DebugDispManualEdgeCollisionDB(EdgeDBEntry *, void *, void *);

void DebugDispManualEdgeCollisionFinder(EdgeFinder *f, void *a1, void *a2)
{
    int i;

    for (i = 0; i < (f->p4 < f->p0 ? f->p4 : f->p0); i++) {
        if (f->entries[i].p0 != 0) {
            DebugDispManualEdgeCollisionDB(&f->entries[i], a1, a2);
        }
    }
}
