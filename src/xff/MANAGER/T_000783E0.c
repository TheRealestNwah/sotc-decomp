typedef int s128 __attribute__((mode(TI)));
extern char *GetScriptLayoutClass(void *);
extern void *dynamic_cast_to_camera_obj(void *);
extern char *get_camera_obj_layout_class(void *);
extern char *GetLightClass(void *);
extern char *GetLayoutClass(unsigned char *);
extern void *GetSubLinkClass(void *);
extern void SetGeometryPointerGlobalState(void *, void *, void *);
extern void DeleteTwoWayLink(void *);
extern void isysRequestDeleteObj(void *);
extern char IdentityQuaternion[];
extern char ZeroPoint[];

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

static void T_000783E0(unsigned char *o)
{
    if (layoutClass(o) != 0) {
        char *l = GetLayoutClass(o);
        if (*(int *)(l + 0x124) != 0) {
            *(s128 *)(l + 0x60) = **(s128 **)(l + 0x13C);
            SetGeometryPointerGlobalState(l + 0xC0, IdentityQuaternion, ZeroPoint);
            DeleteTwoWayLink(l + 0x100);
            *(int *)(l + 0x124) = 0;
        }
    } else if (GetSubLinkClass(o) != 0) {
        isysRequestDeleteObj(o);
    }
}
