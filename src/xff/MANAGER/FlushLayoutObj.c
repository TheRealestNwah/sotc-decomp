extern char *GetScriptLayoutClass(void *);
extern void *dynamic_cast_to_camera_obj(void *);
extern char *get_camera_obj_layout_class(void *);
extern char *GetLightClass(void *);

static inline char *layoutClass(unsigned char *o)
{
    switch (o[8]) {
    case 0xA:
        return (char *)o + 0x20;
    case 0xB:
        return GetScriptLayoutClass(o) + 0x70;
    case 0x11:
        return get_camera_obj_layout_class(dynamic_cast_to_camera_obj(o));
    case 0x13:
        return GetLightClass(o);
    case 9:
    case 0xD:
    case 0x16:
        return (char *)o + 0x90;
    default:
        return 0;
    }
}

typedef int qword __attribute__((mode(TI)));

extern char IdentityQuaternion[];
extern char ZeroPoint[];
extern char *GetLayoutClass(void *);
extern void SetGeometryPointerGlobalState(void *, void *, void *);
typedef struct Link { struct Link *next; struct Link *prev; } Link;
extern int DeleteTwoWayLink(Link *);
extern void ReleaseCollisionWork(void *);

int FlushLayoutObj(unsigned char *o)
{
    char *l = layoutClass(o);
    char *c;

    if (*(signed char *)(l + 0x1BA) == 0) {
        c = GetLayoutClass(o);
        if (*(int *)(c + 0x124) != 0) {
            *(qword *)(c + 0x60) = **(qword **)(c + 0x13C);
            SetGeometryPointerGlobalState(c + 0xC0, IdentityQuaternion, ZeroPoint);
            DeleteTwoWayLink((Link *)(c + 0x100));
            *(int *)(c + 0x124) = 0;
        }
        if (*(int *)(l + 0x174) != 0)
            ReleaseCollisionWork(l + 0x174);
        l[0x1BA] = 1;
    }
    return 0;
}
