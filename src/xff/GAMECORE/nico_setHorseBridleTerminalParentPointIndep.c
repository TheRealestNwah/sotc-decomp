typedef struct { char data[0x40]; } GeometryPointer;
typedef struct { char data[0x90]; } ClothChain;
typedef struct { ClothChain *chains; short count; } ClothChainList;
extern float IdentityQuaternion[4];
extern void SetGeometryPointerNodePosState(GeometryPointer *, void *, int, float *, void *);
extern char *GetLayoutClass(void *);
extern void SetClothSingleFixedChainLeafFixGeometryPointer(ClothChain *, GeometryPointer *);
extern void ParentLayoutObj(void *, GeometryPointer *);

void nico_setHorseBridleTerminalParentPointIndep(void *obj, void *target, int node0, void *pos0,
    int node1, void *pos1)
{
    GeometryPointer pointer[2];
    GeometryPointer *first, *second;
    ClothChainList *list;
    ClothChain *chain;
    int i, count;

    SetGeometryPointerNodePosState(&pointer[0], target, node0, IdentityQuaternion, pos0);
    SetGeometryPointerNodePosState(&pointer[1], target, node1, IdentityQuaternion, pos1);
    first = &pointer[0];
    second = &pointer[1];
    list = *(ClothChainList **)(GetLayoutClass(obj) + 0x178);
    count = list->count;
    chain = list->chains;
    for (i = 0; i < count; i++, chain++)
        SetClothSingleFixedChainLeafFixGeometryPointer(chain, (i & 1) ? first : second);
    ParentLayoutObj(obj, &pointer[0]);
}
