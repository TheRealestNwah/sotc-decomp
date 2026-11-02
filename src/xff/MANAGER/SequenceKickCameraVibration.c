extern unsigned char *CreateSubLinkObjByGeometryPointer(char *, int);
extern char *GetGeometryPointerObject(char *);
extern char *GetLayoutClass(char *);
extern int boot_camera_lws_animation(int, char *, void *, unsigned char *,
                                     char *, float);
extern void isysRequestDeleteObj(void *);
extern void SetSubLinkObjDeleteFuncInfo(unsigned char *, int, void *, int);
extern void D_000EE3A0(void);
extern void func_000EE368(void *);

typedef struct {
    int handle;
    int id;
} CameraVibration;

unsigned char *SequenceKickCameraVibration(int id, char *geometry)
{
    unsigned char *link;
    char *parent = 0;
    char *object;
    char *cls;
    CameraVibration copy;
    CameraVibration info;

    link = CreateSubLinkObjByGeometryPointer(geometry, 8);
    for (object = GetGeometryPointerObject(geometry); object != 0;
         object = GetGeometryPointerObject(cls + 0xC0)) {
        cls = GetLayoutClass(object);
        if (cls == 0)
            break;
        parent = object;
        if (*(int *)(cls + 0x124) == 0)
            break;
    }
    info.handle = boot_camera_lws_animation(id, geometry, D_000EE3A0, link,
                                            parent, 0.0f);
    info.id = id;
    copy = info;
    if (copy.handle < 0) {
        isysRequestDeleteObj(link);
        link = 0;
    } else {
        SetSubLinkObjDeleteFuncInfo(link, (int)func_000EE368, &copy, 8);
    }
    return link;
}
