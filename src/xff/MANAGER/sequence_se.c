extern unsigned char *CreateSubLinkObjByGeometryPointer(char *, int);
extern int sePlay3D(int, void *, int, int);
extern void isysRequestDeleteObj(void *);
extern void SetSubLinkObjDeleteFuncInfo(unsigned char *, int, void *, int);
extern void func_000EE660(void *);
extern char *GetSubLinkClass(void *);
extern void sndSepCont(int);
extern void sndSepPause(int);
extern void seStopLoopType(int);

static void func_000EE648(void *obj, int *se);

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

void seSetKeyOnOff(void *obj, int on)
{
    int se = **(int **)(GetSubLinkClass(obj) + 0x10);
    if (on != 0)
        sndSepCont(se);
    else
        sndSepPause(se);
}

static void func_000EE648(void *obj, int *se)
{
    seStopLoopType(*se);
}

static void T_000EE660(void *obj)
{
    isysRequestDeleteObj(obj);
}
