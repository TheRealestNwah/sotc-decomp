typedef int s128 __attribute__((mode(TI)));
typedef struct {
    char *obj;
    int valid;
    int attr;
    int pad0C;
    long parent;
    long pad18;
    s128 normal;
    s128 pos;
    s128 q40;
    char *geom;
} ColPlaneInfo;
typedef union { s128 q; float f[4]; } U128;
extern U128 YUnitVector;
extern U128 ZeroPoint;
extern void *GAMEUTIL_get_parent_object(void *);
extern char *GetCharacterClass(void *);
extern int GAMEUTIL_get_parent_collision_attribute(long *, char *);
extern char *GetLayoutClass(void *);
extern s128 *GetGeometryPointerSurfacePlane(void *);
extern void GetGeometryPointerPosition(void *, void *);

void GAMEUTIL_set_col_plane_info(ColPlaneInfo *cp, char *obj)
{
    cp->obj = obj;
    if (obj != 0) {
        char *src = obj;
        char *parent = GAMEUTIL_get_parent_object(obj);
        int attr;

        if (parent != 0) {
            char *cc = GetCharacterClass(parent);
            int kind = cc != 0 ? *(short *)(cc + 0x370) : -1000000;
            src = kind == 3 ? parent : obj;
        }
        attr = GAMEUTIL_get_parent_collision_attribute(&cp->parent, src);
        cp->attr = attr;
        if (attr == 1) {
            cp->geom = GetLayoutClass(src) + 0xC0;
            cp->normal = *GetGeometryPointerSurfacePlane(cp->geom);
            GetGeometryPointerPosition(&cp->pos, cp->geom);
            cp->q40 = **(s128 **)(GetLayoutClass(obj) + 0x134);
        } else {
            cp->attr = 0;
            cp->parent = 0;
            cp->normal = YUnitVector.q;
            cp->pos = ZeroPoint.q;
            cp->q40 = ZeroPoint.q;
            cp->geom = 0;
        }
        cp->valid = 1;
    } else {
        cp->obj = 0;
        cp->valid = 0;
        cp->attr = 0;
        cp->parent = 0;
        cp->normal = YUnitVector.q;
        cp->pos = ZeroPoint.q;
        cp->q40 = ZeroPoint.q;
        cp->geom = 0;
    }
}
