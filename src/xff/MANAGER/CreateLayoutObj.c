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

extern int GetClothWorkSize(char *);
extern int func_00074270(void *);
extern void *_isysCreateObj(void *, int, int, int, int, int);
extern void isysSetObjImmediateDeleteFunc(void *, int);
static int T_00078520(unsigned char *);
static void T_00078508(unsigned char *);

static inline int layoutWorkSize(int *definition)
{
    int clothSize = 0;
    if (definition[3]) {
        char *module = *(char **)(definition[3] + 8);
        clothSize = GetClothWorkSize(*(char **)(module + 0x20));
    }
    return clothSize + func_00074270(definition);
}

unsigned char *CreateLayoutObj(void *heap, int extra, int *definition)
{
    unsigned char *object = _isysCreateObj(heap, 10, 0x1E0,
        extra + layoutWorkSize(definition), (int)T_00078520, 16);
    if (object) {
        func_000755D0(object, definition);
        CreateClothChildLayoutObj(object, definition[3], 0);
        if (*(int *)(layoutClass(object) + 0x144))
            isysAddGroupWithLinkParam(object, GetLayoutDispObjGroup(), 0, 0);
        isysAddGroupWithLinkParam(object, GetLayoutObjGroup(), 0, 0);
        isysSetObjImmediateDeleteFunc(object, (int)T_00078508);
    }
    return object;
}
