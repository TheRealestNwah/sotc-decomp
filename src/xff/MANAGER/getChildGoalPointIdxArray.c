typedef struct { char pad[0x30]; } Point;
typedef struct { unsigned int n; char pad[0xC]; Point p[1]; } PointTbl;

static inline Point *getPoint(PointTbl *t, int i)
{
    if (t == 0 || i < 0 || i >= t->n)
        return 0;
    return &t->p[i];
}

void *getChildGoalPointIdxArray(PointTbl *t, int i)
{
    Point *p = getPoint(t, i);
    if (p != 0) {
        if (*(int *)((char *)p + 0x14) != 0)
            return (char *)t + *(int *)((char *)p + 0x18);
    }
    return 0;
}
