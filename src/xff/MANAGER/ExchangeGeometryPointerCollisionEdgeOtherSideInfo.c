typedef struct {
    int vertex[3];
    float length;
    int geometry;
    char pad14[0x2C];
} __attribute__((aligned(8))) CollisionEdgeInfo;

extern int GetCollisionEdgePointerOtherSideCollisionEdge(int *, CollisionEdgeInfo *);
extern void MakeGeometryPointerCollisionEdgeInfo(CollisionEdgeInfo *, int *, int, float);

int ExchangeGeometryPointerCollisionEdgeOtherSideInfo(CollisionEdgeInfo *dst, CollisionEdgeInfo *src)
{
    int vertex[4];

    if (GetCollisionEdgePointerOtherSideCollisionEdge(vertex, src)) {
        MakeGeometryPointerCollisionEdgeInfo(dst, vertex, src->geometry == 0, src->length);
        return 1;
    }
    *dst = *src;
    return 0;
}
