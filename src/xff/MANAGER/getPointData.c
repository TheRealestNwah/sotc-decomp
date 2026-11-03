typedef struct {
    char data[0x30];
} PointData;

typedef struct {
    unsigned int count;
    char pad[0xC];
    PointData points[1];
} PointDataSet;

PointData *getPointData(PointDataSet *set, int index)
{
    PointData *p = 0;

    if (set != 0 && index >= 0) {
        p = &set->points[index];
        if (index < set->count) {
            return p;
        }
        p = 0;
    }
    return p;
}
