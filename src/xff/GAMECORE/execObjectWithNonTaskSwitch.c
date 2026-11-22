typedef struct {
    char pad0[0x178];
    float geomCtx;
    char pad17C[0x188 - 0x17C];
    float clipDist;
    char pad18C[0x1AC - 0x18C];
    int busy;
    char pad1B0[0x370 - 0x1B0];
    char lws[0x10];
} GcGlobal;

typedef struct {
    char pad0[0x370];
    short state;
    char pad372[0x534 - 0x372];
    signed char active;
    char pad535[0xD90 - 0x535];
    unsigned char riding;
    char padD91[0x1070 - 0xD91];
    int f1070;
    char pad1074[0x1170 - 0x1074];
    int f1170;
} ScrCharClass;

typedef struct {
    char pad0[0x8];
    unsigned char type;
} ScrObj;

extern GcGlobal gcGlobalVar;
extern int B_0019B860[2];
extern char B_0018B860[0x10000];
extern void *isysGetThisSubThread(void);
extern void *get_main_cameraman_camera_obj(void);
extern float ViewIntervalClip(void *, void *, float);
extern int *GetCharacterClass(void *);
extern char *GetLayoutClass(void *);
extern int StageManagerCheckAreaExist(int);
extern ScrObj *SCRGetGetGeometryPointerLegalParentObj(char *);
extern int ExecCharaGeometryPreprocess(void *, float, float, float);
extern void ExecCharaGeometry(void *, void *);
extern void ExecCharaGeometryPostprocess(void *);
extern void FlushRequestViewIntervalClip(void *);
extern void isysLetterObjDiscardLetterAll(void *);
extern void ExecScriptLwsOrientClass(void *, void *, void *, float, float);
extern void iosJumpRecoverPoint(const char *, ...);

static inline int isOnRideParent(char *lay)
{
    ScrObj *obj;
    int t;

    if (lay == 0 || *(int *)(lay + 0x124) == 0 || (obj = SCRGetGetGeometryPointerLegalParentObj(lay + 0xC0)) == 0) {
        t = 0;
    } else {
        switch (obj->type) {
        case 9:
        case 0xD:
        case 0x16:
            t = 1;
            break;
        default:
            t = 0;
            break;
        }
    }
    return t;
}

static inline void execLwsObj(ScrObj *obj)
{
    float clip;

    if (gcGlobalVar.busy) {
        FlushRequestViewIntervalClip(obj);
        ViewIntervalClip(obj, get_main_cameraman_camera_obj(), gcGlobalVar.clipDist);
    } else {
        clip = ViewIntervalClip(obj, get_main_cameraman_camera_obj(), gcGlobalVar.clipDist);
        ExecScriptLwsOrientClass(obj, get_main_cameraman_camera_obj(), gcGlobalVar.lws, clip, 1.0f / clip);
    }
    isysLetterObjDiscardLetterAll(obj);
}

void execObjectWithNonTaskSwitch(ScrObj *obj)
{
    ScrCharClass *cc;
    float clip;
    int ok;
    unsigned char t = obj->type;

    switch (t) {
    default:
        iosJumpRecoverPoint("scrsetup: execObjectWithNonTaskSwitch: \xa5\xb5\xa5\xdd\xa1\xbc\xa5\xc8\xa4\xb5\xa4\xec\xa4\xc6\xa4\xa4\xa4\xca\xa4\xa4\xa5\xaa\xa5\xd6\xa5\xb8\xa5\xa7\xa5\xaf\xa5\xc8:%s\xa4\xac\xa5\xc7\xa5\xd5\xa5\xa9\xa5\xeb\xa5\xc8" "AI\xbd\xe8\xcd\xfd\xa4\xcb\xa5\xa8\xa5\xf3\xa5\xc8\xa5\xea\xa4\xb5\xa4\xec\xa4\xc6\xa4\xa4\xa4\xde\xa4\xb9(\xbf\xf9)\n");
        return;
    case 9:
        if (gcGlobalVar.busy) {
            FlushRequestViewIntervalClip(obj);
            ViewIntervalClip(obj, get_main_cameraman_camera_obj(), gcGlobalVar.clipDist);
        } else {
            cc = (ScrCharClass *)GetCharacterClass(obj);
            clip = ViewIntervalClip(obj, get_main_cameraman_camera_obj(), gcGlobalVar.clipDist);
            ok = 0;
            if (cc->active != 0) {
                if (((ScrCharClass *)GetCharacterClass(obj))->f1170 == 0 || StageManagerCheckAreaExist(*(int *)(GetLayoutClass(obj) + 0x134)) != 0 ||
                    cc->state == 4 || isOnRideParent(GetLayoutClass(obj)) || cc->riding == 1 || cc->f1070 == 1 || cc->state == 0xB) {
                    ok = ExecCharaGeometryPreprocess(obj, gcGlobalVar.geomCtx, clip, 1.0f / clip);
                }
            }
            if (ok) {
                char *c2 = (char *)GetCharacterClass(obj);
                ExecCharaGeometry(obj, gcGlobalVar.lws);
                c2[0x539] = StageManagerCheckAreaExist(*(int *)(GetLayoutClass(obj) + 0x134));
            }
            ExecCharaGeometryPostprocess(obj);
        }
        isysLetterObjDiscardLetterAll(obj);
        return;
    case 0x16:
        execLwsObj(obj);
        return;
    }
}
