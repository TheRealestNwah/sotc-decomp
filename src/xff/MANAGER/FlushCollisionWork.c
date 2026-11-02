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
extern int FlushCollisionWorkByWorkStruct(void *, int, int, int);

int FlushCollisionWork(unsigned char *o)
{
    char *l = layoutClass(o);
    char *coll = *(char **)(l + 0x184);
    int *work;

    if (coll == 0)
        return 0;
    if (__builtin_expect(*(int *)(l + 0x174) < 0, 1))
        return 0;
    work = *(int **)(coll + 0x20);
    return FlushCollisionWorkByWorkStruct(*(void **)(l + 0x174), work[1], work[4], work[3]);
}
