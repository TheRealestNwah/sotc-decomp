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

int SaveLayoutObjGeo(unsigned char *o)
{
    char *l = layoutClass(o);
    int r;

    if (l == 0)
        return -2;
    r = 0;
    if (*(void **)(l + 0x190) != 0) {
        (*(void (**)(void *))(l + 0x190))(*(void **)(l + 0x1A4));
        r = 1;
    }
    return r ? 0 : -1;
}
