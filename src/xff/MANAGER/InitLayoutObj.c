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

extern int func_000755D0(void *, int *);
extern void CreateClothChildLayoutObj(void *, int, int);
extern void *GetLayoutDispObjGroup(void);
extern void *GetLayoutObjGroup(void);
extern int isysAddGroupWithLinkParam(void *, void *, int, int);

int InitLayoutObj(unsigned char *o, int *def)
{
    int r = func_000755D0(o, def);

    CreateClothChildLayoutObj(o, def[3], 0);
    if (*(int *)(layoutClass(o) + 0x144) != 0)
        isysAddGroupWithLinkParam(o, GetLayoutDispObjGroup(), 0, 0);
    isysAddGroupWithLinkParam(o, GetLayoutObjGroup(), 0, 0);
    return r;
}
