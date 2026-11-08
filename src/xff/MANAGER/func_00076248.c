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
extern void *GetGeometryPointerObject(void *);

static void func_00076248(unsigned char *o)
{
    unsigned char *r;
    char *l;
    char *c;
    unsigned char *p;

    r = 0;
    l = layoutClass(o);
    c = l;

    while (*(int *)(c + 0x124) != 0) {
        p = GetGeometryPointerObject(l + 0xC0);
        c = layoutClass(p);
        if (*(int *)(c + 0x144) != 0)
            r = p;
    }
    *(unsigned char **)(l + 0x198) = r;
}
