typedef union { float f[4]; int q __attribute__((mode(TI))); } Vec4;

extern char *GetLayoutClass(void *);
extern void GetGeometryPointerQuaternion(Vec4 *, char *);
extern void DivQuaternion(char *, Vec4 *, Vec4 *);
extern void *GetGeometryPointerObject(char *);
extern void CopyGeometryPointer(char *, char *);
extern void DeleteTwoWayLink(char *);
extern void AddTwoWayLinkNext(char *, char *);

static inline void setParentRotation(void *object, char *geometry)
{
    Vec4 rotation;
    char *layout = GetLayoutClass(object);

    GetGeometryPointerQuaternion(&rotation, geometry);
    DivQuaternion(layout + 0x60, *(Vec4 **)(layout + 0x13C), &rotation);
}

static inline void setParentLink(void *object, char *geometry)
{
    char *layout = GetLayoutClass(object);
    void *parent = GetGeometryPointerObject(geometry);
    void *oldParent = GetGeometryPointerObject(layout + 0xC0);

    CopyGeometryPointer(layout + 0xC0, geometry);
    if (*(int *)(layout + 0x124) == 0) {
        *(int *)(layout + 0x124) = 1;
    } else {
        if (oldParent == parent)
            return;
        DeleteTwoWayLink(layout + 0x100);
    }
    if (parent != 0)
        AddTwoWayLinkNext(GetLayoutClass(parent) + 0x10C, layout + 0x100);
}

int ParentLayoutObj(void *object, char *geometry)
{
    setParentRotation(object, geometry);
    setParentLink(object, geometry);
    return 0;
}
