typedef union {
    struct {
        int vertex[3];
        float length;
        int geometry;
        char pad14[0x1C];
        int kind;
    } s;
    char alias;
} CollisionEdgeInfo;

void MakeGeometryPointerCollisionEdgeInfo(CollisionEdgeInfo *info, int *vertex, int geometry, float length)
{
    info->s.vertex[0] = vertex[0];
    info->s.vertex[1] = vertex[1];
    info->s.vertex[2] = vertex[2];
    info->s.length = length;
    info->s.geometry = geometry;
    info->s.kind = 4;
}
