typedef struct { int emitter; void *owner; } WindInfo;
extern unsigned char *CreateSubLinkObjByGeometryPointer(char *, int);
extern void *GetGeometryPointerObject(char *);
extern int boot_wind_emitter_by_judge_volume(void *, void *, int, unsigned char *);
extern void isysRequestDeleteObj(void *);
extern void SetSubLinkObjDeleteFuncInfo(unsigned char *, int, void *, int);
extern void T_000EE8C8(void *);
static void func_000EE890(void *, WindInfo *);

unsigned char *SequenceKickWindVolumeShape(void *owner, char *geometry)
{
    unsigned char *link;
    WindInfo copy, info;
    char *pointer = geometry + 0x10;
    link = CreateSubLinkObjByGeometryPointer(pointer, 8);
    info.emitter = boot_wind_emitter_by_judge_volume(owner,
        GetGeometryPointerObject(pointer), (int)T_000EE8C8, link);
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
