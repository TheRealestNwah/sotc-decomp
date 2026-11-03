typedef struct { char data[0x40]; } GeometryPointer;
typedef struct { char data[0x90]; } ClothChain;
typedef struct { ClothChain *chains; short count; } ClothChainList;
typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; struct { float x, y, z, w; } v; } Vec4;

extern float IdentityQuaternion[4];
extern void SetGeometryPointerNodePosState(GeometryPointer *, void *, int, float *, void *);
extern char *GetLayoutClass(void *);
extern void SetClothSingleFixedChainLeafFixGeometryPointer(ClothChain *, GeometryPointer *);
extern void ParentLayoutObj(void *, GeometryPointer *);

void nico_setHorseBridleTerminalParentPoint(void *obj, void *target, int node, Vec4 *pos, float ofs)
{
    GeometryPointer pointer[2];
    Vec4 p;
    GeometryPointer *first, *second;
    ClothChainList *list;
    ClothChain *chain;
    int i, count;

    p.q = pos->q;
    p.v.x = pos->v.x - ofs;
    SetGeometryPointerNodePosState(&pointer[0], target, node, IdentityQuaternion, &p);
    p.v.x = pos->v.x + ofs;
    SetGeometryPointerNodePosState(&pointer[1], target, node, IdentityQuaternion, &p);
    first = &pointer[0];
    second = &pointer[1];
    list = *(ClothChainList **)(GetLayoutClass(obj) + 0x178);
    count = list->count;
    chain = list->chains;
    for (i = 0; i < count; i++, chain++)
        SetClothSingleFixedChainLeafFixGeometryPointer(chain, (i & 1) ? first : second);
    ParentLayoutObj(obj, &pointer[0]);
}
