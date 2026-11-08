#ifdef NONMATCHING
/* Parked: 22 words differ (success path is not a sibling call; loop-invariant lui placement) */
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
extern char rootPtn[];
extern int InitCollisionWork(void *, int, void *, int);
extern int GetCollisionWorkSize(int);
extern void EntryObjectManagerCollisionGroup(void *, int);
extern void isysSleepSubThread(void);
static void func_000748C0(unsigned char *o)
{
    char *l;
    int w;

    l = layoutClass(o);
    while (*(int *)(l + 0x174) < 0) {
        w = InitCollisionWork(rootPtn, *(int *)(*(int *)(l + 0x184) + 0x20), l, 1);
        if (w != 0) {
            l = layoutClass(o);
            *(int *)(l + 0x174) = w;
            *(char *)(l + 0x1BB) = 1;
            *(int *)(l + 0x148) = GetCollisionWorkSize(*(int *)(*(int *)(l + 0x184) + 0x20));
            EntryObjectManagerCollisionGroup(o, *(int *)(l + 0x17C));
            return;
        }
        isysSleepSubThread();
    }
}
#endif
