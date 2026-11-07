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

extern void SetClothAccessSwitch(int, int);
extern void *GetTwoWayLinkNext(void *);
extern unsigned char *GetTwoWayLinkData(void *);
extern void SetScriptAnimationObjAccessSwitch(unsigned char *, int);

static inline char *setClassSwitch(unsigned char *o, int sw)
{
    char *c = layoutClass(o);

    if (c && *(signed char *)(c + 0x1B8) != sw) {
        *(signed char *)(c + 0x1B8) = sw;
        if (*(int *)(c + 0x180))
            SetClothAccessSwitch(*(int *)(c + 0x178), sw);
        return c;
    }
    return 0;
}

int SetLayoutObjAccessSwitch(unsigned char *o, int sw)
{
    char *c = setClassSwitch(o, sw);
    void *link;

    do {
        if (c == 0)
            return 0;
        for (link = GetTwoWayLinkNext(c + 0x10C); link != 0; link = GetTwoWayLinkNext(link)) {
            unsigned char *d = GetTwoWayLinkData(link);

            if (d[8] == 0xD)
                SetScriptAnimationObjAccessSwitch(d, sw);
            else
                SetLayoutObjAccessSwitch(d, sw);
        }
    } while (0);
    return 1;
}
