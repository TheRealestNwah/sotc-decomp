typedef int s128 __attribute__((mode(TI)));
extern void GetCollisionDBAttribute(s128 *, void *);

void GetGeometryPointerSurfaceAttribute(s128 *out, char *g)
{
    void *db;
    switch (*(unsigned int *)(g + 0x30)) {
    case 2:
    case 3:
    case 4:
    case 5:
        db = g;
        break;
    case 0:
    case 1:
    case 6:
    case 7:
    case 8:
        db = 0;
        break;
    default:
        db = 0;
        break;
    }
    if (db != 0) {
        GetCollisionDBAttribute(out, db);
        return;
    }
    *out = 0;
}
