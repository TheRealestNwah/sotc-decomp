typedef struct { signed char a; signed char place; char pad[0x42]; } SavePoint;
typedef struct { char pad[0xC]; int n; SavePoint *list; } SavePointList;
extern SavePointList SH_SavePointDEFAULT;

SavePoint *gStatPlaceIdToSavePoint(int place)
{
    int i = 0;
    int n = SH_SavePointDEFAULT.n;
    SavePoint *s = SH_SavePointDEFAULT.list;
    for (; i < n; i++, s++) {
        if (s->place == place)
            return s;
    }
    return 0;
}
