typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;
typedef struct { int f0; int id; } FinderEntry;
extern int ClipCollisionDB(void *, s128 *, float *, void *);
extern void func_0009D8F8(s128 *, FinderEntry *, float *, int);

int ClipCollisionFinder4D(char *out, float *start, Vec4 *finish, int *finder)
{
    int count = finder[1] < finder[0] ? finder[1] : finder[0];
    FinderEntry *entry = (FinderEntry *)finder[3];
    FinderEntry *found;
    int remaining;
    Vec4 end;
    s128 local;

    if (count != 0) {
        end.q = finish->q;
        found = 0;
        for (remaining = count - 1; remaining != -1; remaining--) {
            if (entry->f0 != 0) {
                func_0009D8F8(&local, entry, start, 1);
                if (ClipCollisionDB(out, &local, end.f, entry)) {
                    end.q = *(s128 *)(out + 0x40);
                    found = entry;
                }
            }
            entry++;
        }
        if (found != 0) {
            *(int *)out = found->f0;
            *(int *)(out + 4) = found->id;
        }
        return 0;
    }
    return 0;
}
