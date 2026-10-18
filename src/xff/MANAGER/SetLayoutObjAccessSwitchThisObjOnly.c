extern void *GetScriptLayoutClass(unsigned char *);
extern void *dynamic_cast_to_camera_obj(void *);
extern int get_camera_obj_layout_class(int);
extern char *GetLightClass(unsigned char *);

static inline char *layoutClass(unsigned char *o)
{
    switch (o[8]) {
    case 0xA:
        return (char *)o + 0x20;
    case 0xB:
        return (char *)GetScriptLayoutClass(o) + 0x70;
    case 0x11:
        return (char *)get_camera_obj_layout_class((int)dynamic_cast_to_camera_obj(o));
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

extern void SetClothAccessSwitch(void *, int);
char *SetLayoutObjAccessSwitchThisObjOnly(unsigned char *object, int enabled)
{
    char *layout = layoutClass(object);
    if (layout && *(signed char *)(layout + 0x1B8) != enabled) {
        *(signed char *)(layout + 0x1B8) = enabled;
        if (*(int *)(layout + 0x180))
            SetClothAccessSwitch(*(void **)(layout + 0x178), enabled);
        return layout;
    }
    return 0;
}
