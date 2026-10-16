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

extern void ChangeCollisionResourceAttribute(void *, int, int, int, int, int, int);

void ChangeLayoutObjCollisionResourceAttribute(unsigned char *o, int a, int b, int c, int d, int e, int f)
{
    void *r = *(void **)(*(char **)(layoutClass(o) + 0x184) + 0x20);

    if (r != 0)
        ChangeCollisionResourceAttribute(r, a, b, c, d, e, f);
}
