typedef struct ModMgr {
    char pad[0x14];
    int work;
} ModMgr;

typedef struct CollEntry {
    ModMgr m[4];
} CollEntry;

typedef struct CollSrc {
    int n0;
    char pad04[0xC];
    int n1;
    char pad14[0x7C];
} CollSrc;

typedef struct CollData {
    int pad0;
    int count;
    CollSrc *src;
    int n0;
    int n1;
} CollData;

typedef struct CollWork {
    char pad00[0x10];
    char link[0x14];
    CollEntry *entries;
    ModMgr m[4];
    int layout;
    char pad8C[4];
} CollWork;

extern void SetLayoutClassCollisionWorkAdr(int, void *);
extern void RelocateTwoWayLinkHeader(void *);
extern int RelocateModifiedManager(void *, int, char *);
extern int GetSizeOfModifiedManagerWork(int);

void RelocateCollisionWork(char *p, CollData *data)
{
    CollWork *work = (CollWork *)p;
    int count = data->count;
    int i;
    int n0;
    int n1;

    SetLayoutClassCollisionWorkAdr(work->layout, work);
    RelocateTwoWayLinkHeader(work->link);
    p += sizeof(CollWork);
    work->entries = (CollEntry *)p;
    p += count * sizeof(CollEntry);
    for (i = 0; i < count; i++) {
        n0 = data->src[i].n0;
        n1 = data->src[i].n1;
        work->entries[i].m[0].work = RelocateModifiedManager(&work->entries[i].m[0], n0, p);
        p += GetSizeOfModifiedManagerWork(n0) + n0 * 16;
        work->entries[i].m[1].work = RelocateModifiedManager(&work->entries[i].m[1], n0, p);
        p += GetSizeOfModifiedManagerWork(n0) + n0 * 16;
        work->entries[i].m[2].work = RelocateModifiedManager(&work->entries[i].m[2], n1, p);
        p += GetSizeOfModifiedManagerWork(n1) + n1 * 16;
        work->entries[i].m[3].work = RelocateModifiedManager(&work->entries[i].m[3], n1, p);
        p += GetSizeOfModifiedManagerWork(n1) + n1 * 16;
    }
    n0 = data->n0;
    n1 = data->n1;
    work->m[0].work = RelocateModifiedManager(&work->m[0], n0, p);
    p += GetSizeOfModifiedManagerWork(n0) + n0 * 16;
    work->m[1].work = RelocateModifiedManager(&work->m[1], n0, p);
    p += GetSizeOfModifiedManagerWork(n0) + n0 * 16;
    work->m[2].work = RelocateModifiedManager(&work->m[2], n1, p);
    p += GetSizeOfModifiedManagerWork(n1) + n1 * 16;
    work->m[3].work = RelocateModifiedManager(&work->m[3], n1, p);
    p += GetSizeOfModifiedManagerWork(n1) + n1 * 16;
}
