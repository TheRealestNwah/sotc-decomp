typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;
typedef struct { int f0; int id; } FinderEntry;
extern int ClipCollisionDB(void *, float *, float *, void *);

FinderEntry *ClipCollisionFinder(char *out, float *start, Vec4 *finish, int *finder)
{
    int count = finder[0];
    if (finder[1] < count)
        count = finder[1];
    if (count != 0) {
        Vec4 end;
        FinderEntry *entry = (FinderEntry *)finder[3];
        FinderEntry *found = 0;
        int remaining;
        end.q = finish->q;
        for (remaining = count - 1; remaining != -1; remaining--) {
            if (entry->f0 != 0 && ClipCollisionDB(out, start, end.f, entry)) {
                end.q = *(s128 *)(out + 0x40);
                found = entry;
            }
            entry++;
        }
        if (found != 0) {
            *(int *)out = found->f0;
            *(int *)(out + 4) = found->id;
        }
        return found;
    }
    return 0;
}
