typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;
typedef struct { int object, id; char unknown[0xC]; } EdgeEntry;
typedef struct { char pad0[0x20]; int count; EdgeEntry *entries; } EdgeFinder;
extern void *memset(void *, int, unsigned int);
extern int func_000A41A0(Vec4 *, float *, Vec4 *, EdgeEntry *, Vec4 *);

int ClipEdgeLinkDBFinder(Vec4 *out, float *start, Vec4 *finish, EdgeFinder *finder, float height)
{
    int hits = 0;
    int remaining = finder->count;
    EdgeEntry *entry = finder->entries;
    if (remaining != 0) {
        Vec4 end;
        Vec4 parameters;
        memset(&parameters, 0, 16);
        parameters.f[1] = height;
        end.q = finish->q;
        if (remaining > 0) {
          do {
            if (func_000A41A0(out, start, &end, entry, &parameters)) {
                end.q = out->q;
                hits++;
            }
            remaining--;
            entry++;
          } while (remaining != 0);
        }
    }
    return hits != 0;
}
