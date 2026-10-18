typedef struct Link { struct Link *next; struct Link *prev; } Link;
extern char *GetLayoutClass(unsigned char *);
extern void *GetGeometryPointerObject(char *);
extern void CopyGeometryPointer(void *, void *);
extern int DeleteTwoWayLink(Link *);
extern int AddTwoWayLinkNext(int *, int *);
int ForceParentLayoutObj(void *object, void *geometry)
{
    char *layout = GetLayoutClass(object);
    char *storedGeometry = layout + 0xC0;
    void *newParent = GetGeometryPointerObject(geometry);
    void *oldParent = GetGeometryPointerObject(storedGeometry);
    CopyGeometryPointer(storedGeometry, geometry);
    if (*(int *)(layout + 0x124) == 0)
        *(int *)(layout + 0x124) = 1;
    else {
        if (oldParent == newParent)
            return 0;
        DeleteTwoWayLink((Link *)(layout + 0x100));
    }
    if (newParent != 0) {
        char *parentLayout = GetLayoutClass(newParent);
        AddTwoWayLinkNext((int *)(parentLayout + 0x10C), (int *)(layout + 0x100));
    }
    return 0;
}
