extern unsigned char *CreateSubLinkObjByGeometryPointer(char *, int);
extern int sePlay3D(int, void *, int, int);
extern void isysRequestDeleteObj(void *);
extern void SetSubLinkObjDeleteFuncInfo(unsigned char *, int, void *, int);
extern void func_000EE648(void *, int *);
extern void func_000EE660(void *);

unsigned char *SequenceKickSE(int sound, char *geometry)
{
    unsigned char *link;
    int handle;

    link = CreateSubLinkObjByGeometryPointer(geometry, 4);
    handle = sePlay3D(sound, geometry, (int)link, (int)func_000EE660);
    if (handle == 0) {
        isysRequestDeleteObj(link);
        link = 0;
    } else {
        SetSubLinkObjDeleteFuncInfo(link, (int)func_000EE648, &handle, 4);
    }
    return link;
}
