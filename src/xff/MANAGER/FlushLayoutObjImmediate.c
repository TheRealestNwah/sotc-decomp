/* Parked: 17 diffs. Permuter-found shape (the (unsigned short) offset and
 * the pp/one temporaries) fixes the s0/s1 swap of the plain version (40 diffs).
 * Remaining: l + 0x1A4 is kept in s0 across the second DeleteAllTwoWayLink
 * call (one extra addiu) instead of reloading lw 0x1A4(s1) after it, and the
 * li 1 / lw / beqz / sb tail is scheduled differently. */
#ifdef NONMATCHING
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

extern void D_000783E0(void);
extern void func_000783D8(void);
extern void DeleteAllTwoWayLink(void *, void (*)(void));
extern void modelDeleteDispModelClass(void *);
extern int GetLayoutDispObjGroup(void);
extern void _isysDeleteGroup(void *, int, int);
extern void FlushClothWork(void *);
extern void isysRequestDeleteObj(int);
extern void FlushCollisionWorkImmediate(int);

static inline int callRelease(char *l)
{
    void (*f)(void *) = *(void (**)(void *))(l + 0x190);
    int r;

    if (f != 0) {
        f(*(void **)(l + 0x1A4));
        r = 1;
    } else {
        r = 0;
    }
    return r;
}

void FlushLayoutObjImmediate(unsigned char *o)
{
    char **pp;
    int one;
    char *l = layoutClass(o);
    int w;

    if (callRelease(l))
        *(int *)(l + 0x190) = 0;
    if (*(void **)(l + (unsigned short)0x144) != 0) {
        modelDeleteDispModelClass(*(void **)(l + 0x144));
        _isysDeleteGroup(o, GetLayoutDispObjGroup(), 0);
    }
    if (*(int *)(l + 0x180) != 0)
        FlushClothWork(o);
    if (*(int *)(l + 0x184) != 0 && (w = *(int *)(l + 0x174)) != 0) {
        if (w < 0) {
            isysRequestDeleteObj(w & 0x7FFFFFFF);
            *(int *)(l + 0x174) = 0;
        } else {
            FlushCollisionWorkImmediate(w);
        }
    }
    DeleteAllTwoWayLink(layoutClass(o) + 0x10C, D_000783E0);
    pp = (char **)(l + 0x1A4);
    DeleteAllTwoWayLink(l + 0x118, func_000783D8);
    {
        char *p;
        one = 1;
        p = *pp;
        *(char *)(l + 0x151) = one;
        if (p != 0)
            *(int *)(p + 8) = 0;
    }
}
#endif
