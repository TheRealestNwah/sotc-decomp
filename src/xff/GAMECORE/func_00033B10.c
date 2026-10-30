typedef struct {
    float x, y, z, w;
} __attribute__((aligned(16))) Vec4;

typedef struct {
    char unknown00[0x4C];
    int unknown4C;
    char unknown50[0x40];
    int bubble;
    int arrow;
    char unknown98[4];
    int bubbleKeep;
    char unknownA0[6];
    short unknownA6;
    char unknownA8[0xC];
    float height;
} ArrowWork;

extern char ZeroPoint[];
extern char IdentityQuaternion[];
extern int ScriptAnimationObjDef_ARROW_EFF_WATER;
extern int ScriptAnimationObjDef_ARROW_EFF_BUBBLE;
extern void GetGeometryPointerPosition(Vec4 *, void *);
extern char *SetLayoutObjAccessSwitchThisObjOnly(int, int);
extern void SetGeometryPointerNodePosState(void *, int, int, void *, void *);
extern void GetStabYRotQuaternion(Vec4 *, ArrowWork *);
extern int _SCRSetupLWS(int, void *, void *, void *, int);
extern void _SCRStartLWS(int, int, int, int);
extern void isysRequestDeleteObj(int);

static void func_00033B10(ArrowWork *work, void *geometry)
{
    Vec4 rotation;
    char node[0x40];
    Vec4 position;

    GetGeometryPointerPosition(&position, geometry);
    work->height = position.y;
    SetLayoutObjAccessSwitchThisObjOnly(work->arrow, 1);
    SetGeometryPointerNodePosState(node, work->arrow, 0, IdentityQuaternion, ZeroPoint);
    GetStabYRotQuaternion(&rotation, work);
    _SCRStartLWS(_SCRSetupLWS(ScriptAnimationObjDef_ARROW_EFF_WATER, 0, &position, IdentityQuaternion, 0), -1, 3, 0);
    work->unknownA6 = 1;
    work->unknown4C = -1;
    if (work->bubble && !work->bubbleKeep)
        isysRequestDeleteObj(work->bubble);
    work->bubble = 0;
    work->bubbleKeep = 0;
    work->bubble = _SCRSetupLWS(ScriptAnimationObjDef_ARROW_EFF_BUBBLE, node, ZeroPoint, IdentityQuaternion, 0);
    _SCRStartLWS(work->bubble, -1, 5, 0);
}
