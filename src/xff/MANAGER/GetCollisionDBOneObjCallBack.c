#ifdef NONMATCHING /* 48 diffs: the second loop count should stay in s0 instead of being reloaded, which shifts the s-register assignment */
extern char *GetLayoutClass(void *);

typedef struct { void *obj; unsigned int id; } ColRef;
typedef struct { char pad0[4]; int count; char *items; } ColDB;

void GetCollisionDBOneObjCallBack(void *o, void (*cb)(ColRef *, void *), void *arg)
{
    char *cls = GetLayoutClass(o);
    ColDB *db;
    char *e;
    int i;

    if (cls[0x1BB] == 0)
        return;
    if (cls[0x1B8] == 0)
        return;
    db = *(ColDB **)(*(char **)(cls + 0x184) + 0x20);
    e = db->items;
    for (i = 0; i < db->count; i++, e += 0x90) {
        int j;
        if (*(int *)(e + 4) == 0)
            continue;
        if (*(int *)(e + 0x10) != 0) {
            for (j = 0; j < *(int *)(e + 0x10); j++) {
                ColRef r;
                r.obj = o;
                r.id = (i << 24) | j | 0x80000000;
                cb(&r, arg);
            }
        }
        if (*(int *)(e + 0x50) != 0) {
            for (j = 0; j < *(int *)(e + 0x50); j++) {
                ColRef r;
                r.obj = o;
                r.id = (i << 24) | j;
                cb(&r, arg);
            }
        }
    }
}
#endif
