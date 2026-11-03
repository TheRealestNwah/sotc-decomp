extern int GetSizeOfModifiedManagerWork(int);

typedef struct {
    int a;
    int pad4[3];
    int b;
    char pad14[0x90 - 0x14];
} ModEntry;

typedef struct {
    int pad0;
    int n;
    ModEntry *e;
    int a;
    int b;
} ModList;
static inline int sz(int a) { return GetSizeOfModifiedManagerWork(a) + a * 16; }
int GetCollisionWorkSize(ModList *m)
{
    int n = m->n;
    int size = n * 0x60 + 0x90;
    int i;
    for (i = 0; i < n; i++) {
        int a = m->e[i].a, b = m->e[i].b;
        size += sz(a); size += sz(a); size += sz(b); size += sz(b);
    }
    {
        int a = m->a, b = m->b;
        size += sz(a); size += sz(a); size += sz(b); size += sz(b);
    }
    return size + 0x33;
}
