typedef struct { int emitter; void *owner; } WindInfo;
extern unsigned char *CreateSubLinkObjByGeometryPointer(char *, int);
extern int boot_wind_emitter(void *, char *, int, unsigned char *);
extern int boot_wind_emitter_by_box(void *, char *, int, unsigned char *);
extern void isysRequestDeleteObj(void *);
extern void SetSubLinkObjDeleteFuncInfo(unsigned char *, int, void *, int);
extern void T_000EE8C8(void *);
extern int stop_wind_emitter_callback(unsigned int);
extern int end_wind_emitter(unsigned int);
extern int stop_wind_emitter_geometry_pointer_reference(unsigned int);
static void func_000EE890(void *, WindInfo *);

unsigned char *SequenceKickWind(void *owner, char *geometry)
{
    unsigned char *link;
    WindInfo copy, info;
    link = CreateSubLinkObjByGeometryPointer(geometry + 0x10, 8);
    info.emitter = boot_wind_emitter(owner, geometry, (int)T_000EE8C8, link);
    info.owner = owner;
    copy = info;
    if (copy.emitter < 0) {
        isysRequestDeleteObj(link);
        link = 0;
    } else {
        SetSubLinkObjDeleteFuncInfo(link, (int)func_000EE890, &copy, sizeof(copy));
    }
    return link;
}

unsigned char *SequenceKickWindBox(void *owner, char *geometry)
{
    unsigned char *link;
    WindInfo copy, info;
    link = CreateSubLinkObjByGeometryPointer(geometry + 0x10, 8);
    info.emitter = boot_wind_emitter_by_box(owner, geometry, (int)T_000EE8C8, link);
    info.owner = owner;
    copy = info;
    if (copy.emitter < 0) {
        isysRequestDeleteObj(link);
        link = 0;
    } else {
        SetSubLinkObjDeleteFuncInfo(link, (int)func_000EE890, &copy, sizeof(copy));
    }
    return link;
}

static void func_000EE890(void *object, WindInfo *info)
{
    stop_wind_emitter_callback(info->emitter);
    end_wind_emitter(info->emitter);
    stop_wind_emitter_geometry_pointer_reference(info->emitter);
}
