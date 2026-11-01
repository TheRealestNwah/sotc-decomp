typedef int s128 __attribute__((mode(TI)));
typedef union {
    s128 q;
    int i[4];
} Vector;
extern Vector YUnitVector;
extern void *iosMallocAlign(void *, int, int);

typedef struct {
    Vector up;
    int count;
    int id;
    int p18;
    int p1C;
    int p20;
    void *links;
} EdgeLinkDB;

EdgeLinkDB *InitCollisionEdgeLinkDB(void *heap, int count)
{
    EdgeLinkDB *db;
    void *links;

    if (count != 0) {
        db = iosMallocAlign(heap, 0x30, 0x10);
        links = iosMallocAlign(heap, count * 20, 4);
        db->id = -1;
        ((unsigned char *)db)[0x12] = 0;
        db->p18 = 0;
        db->p1C = 0;
        db->up.q = YUnitVector.q;
        db->links = links;
        db->count = count;
        db->p20 = 0;
        return db;
    }
    return 0;
}
