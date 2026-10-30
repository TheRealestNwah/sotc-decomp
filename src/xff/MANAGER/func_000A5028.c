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

static int func_000A5028(ModList *m)
{
    int n = m->n;
    int size = n * 0x60 + 0x90;
    int i;
    int a;
    int b;

    for (i = 0; i < n; i++) {
        a = m->e[i].a;
        b = m->e[i].b;
        size += GetSizeOfModifiedManagerWork(a) + a * 16;
        size += GetSizeOfModifiedManagerWork(a) + a * 16;
        size += GetSizeOfModifiedManagerWork(b) + b * 16;
        size += GetSizeOfModifiedManagerWork(b) + b * 16;
    }
    a = m->a;
    b = m->b;
    size += GetSizeOfModifiedManagerWork(a) + a * 16;
    size += GetSizeOfModifiedManagerWork(a) + a * 16;
    size += GetSizeOfModifiedManagerWork(b) + b * 16;
    size += GetSizeOfModifiedManagerWork(b) + b * 16;
    return size;
}
