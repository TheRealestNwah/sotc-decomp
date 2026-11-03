typedef struct CollisionReference {
    void *object;
    unsigned int packed;
} CollisionReference;

typedef struct CollisionDBItem {
    char pad0[4];
    int enabled;
    char pad8[8];
    int edgeCount;
    char pad14[0x3C];
    int vertexCount;
    char pad54[0x3C];
} CollisionDBItem;

typedef struct CollisionDBList {
    char pad0[4];
    int count;
    CollisionDBItem *items;
} CollisionDBList;

typedef struct CollisionDBGeom {
    char pad0[0x20];
    CollisionDBList *list;
} CollisionDBGeom;

typedef struct LayoutClass {
    char pad0[0x184];
    CollisionDBGeom *geom;
    char pad188[0x30];
    char valid;
    char pad1B9[2];
    char active;
} LayoutClass;

extern LayoutClass *GetLayoutClass(void *);

static inline void callRef(void *object, unsigned int packed, void (*callback)(CollisionReference *, void *), void *user)
{
    CollisionReference ref;
    ref.object = object;
    ref.packed = packed;
    callback(&ref, user);
}

void GetCollisionDBOneObjCallBack(void *object, void (*callback)(CollisionReference *, void *), void *user)
{
    LayoutClass *layout = GetLayoutClass(object);
    CollisionDBList *list;
    CollisionDBItem *item;
    int i, j, k, n;

    if (layout->active == 0) return;
    if (layout->valid == 0) return;
    list = layout->geom->list;
    item = list->items;
    for (i = 0; i < list->count; i++, item++) {
        if (item->enabled == 0) continue;
        if (item->edgeCount != 0) {
            for (j = 0; j < item->edgeCount; j++) {
                callRef(object, (i << 24) | j | 0x80000000, callback, user);
            }
        }
        n = item->vertexCount;
        if (n != 0) {
            for (k = 0; k < n; k++) {
                callRef(object, (i << 24) | k, callback, user);
            }
        }
    }
}
