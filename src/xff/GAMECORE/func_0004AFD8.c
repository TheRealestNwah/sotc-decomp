extern void meshObjectFree(void *object);

typedef struct {
    char pad0[0x50];
    int count;
} Mesh;

typedef struct {
    int unk0;
    Mesh *mesh;
    char pad8[0xC];
    void *objs[1];
} MeshSet;

static void func_0004AFD8(void *unused, MeshSet *set)
{
    Mesh *mesh = set->mesh;
    int i;

    for (i = 0; i < mesh->count; i++) {
        if (set->objs[i] != 0) {
            meshObjectFree(set->objs[i]);
        }
    }
}
