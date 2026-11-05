typedef struct {
    char pad0[4];
    int active;
    char pad8[8];
    int planeCount;
    char pad14[0x3C];
    int sphereCount;
    char pad54[0x3C];
} CollisionNode;

typedef struct {
    char pad0[4];
    int nodeCount;
    CollisionNode *nodes;
} CollisionResource;

typedef struct {
    char pad0[0x20];
    CollisionResource *resource;
} CollisionFile;

typedef struct {
    char pad0[0x184];
    CollisionFile *collision;
    char pad188[0x30];
    char enabled;
    char pad1B9[2];
    char visible;
} LayoutClass;

typedef struct {
    int object;
    unsigned packed;
} CollisionReference;

typedef struct {
    int obj;
} SysGroup;

extern SysGroup *isysGroupForFirst(void *, int);
extern SysGroup *isysGroupForNext(SysGroup *, int);
extern void isysGroupForExit(int, int);
extern LayoutClass *GetLayoutClass(int);

#ifdef NONMATCHING
/* 81 diffs: the second reference address is hoisted into a saved register, so the callback is spilled to the stack instead of the group object */
void GetCollisionDBGroupCallBack(void *head, void (*callback)(CollisionReference *, void *), void *user)
{
    SysGroup *group = isysGroupForFirst(head, 0);
    int last = 0;

    while (group != 0) {
        LayoutClass *layout;
        last = group->obj;
        layout = GetLayoutClass(last);
        if (layout->visible != 0 && layout->enabled != 0) {
            CollisionResource *resource = layout->collision->resource;
            CollisionNode *node = resource->nodes;
            int n;
            for (n = 0; n < resource->nodeCount; n++, node++) {
                int i;
                int count;
                if (node->active == 0)
                    continue;
                if (node->planeCount != 0) {
                    for (i = 0; i < node->planeCount; i++) {
                        CollisionReference ref;
                        ref.object = last;
                        ref.packed = (n << 24) | i | 0x80000000;
                        callback(&ref, user);
                    }
                }
                count = node->sphereCount;
                if (count != 0) {
                    for (i = 0; i < count; i++) {
                        CollisionReference ref;
                        ref.object = last;
                        ref.packed = (n << 24) | i;
                        callback(&ref, user);
                    }
                }
            }
        }
        group = isysGroupForNext(group, 0);
    }
    if (last != 0)
        isysGroupForExit(last, 0);
}
#endif
