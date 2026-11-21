typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } V4;

extern int isysGetThisSubThread(void);
extern char *GetCharacterClass(int);
extern char *GetLayoutClass(int);
extern char **GetAnimationClass(int);
extern void CharaCtrlResetAllScriptCtrlStatus(int);
extern void setExecRayChkPathWork(char *, int);
extern int ClipCollisionDirect(void *, void *, void *, void *);
extern void SetObjectGeoAndUnparent(int, int, void *);
extern void DebugSetObjectGeometry(int, int, void *);
extern int GetGeometryPointerObject(void *);
extern int SCRGetFirstObj(void *);
extern int getNearPointPosUserPathWork(void *, void *, void *, int, int);
extern char *getPassageWork(char *, int);
extern char *getPointDataByAreaIdx(char *, int, int);
extern void deletePassageWork(char *, int);
extern int GetStageAreaNumberByPos(void *);
extern int getPathDataAddr(char *, int);
extern void setFreezeHorseCtrlWork(char *, int);
extern void updateScriptDataSystem(int);
extern char gcGlobalVar[];
extern char *StageLayout_COMPULSION_DEATH_COLI;
extern int ControlMode_PLAYER_DEATH;

#define ANIMSPD(o) (*GetAnimationClass(o) != 0 ? *(float *)(*GetAnimationClass(o) + 0xB4) : 0.0f)

static void func_00056C60(char *w)
{
    struct {
        char hit[0x50];
        V4 s, e;
    } L;
    int obj = isysGetThisSubThread();
    signed char on = *(signed char *)(GetCharacterClass(obj) + 0xCEC);
    int found;
    char *pw;
    float v;

    CharaCtrlResetAllScriptCtrlStatus(obj);
    if (ANIMSPD(obj) > 0.0f) {
        v = *(float *)(w + 0x4220) = *(float *)(w + 0x4220) + *(float *)(gcGlobalVar + 0x190) * ANIMSPD(obj);
        if (!(v <= 100.0f))
            v = 100.0f;
        *(float *)(w + 0x4220) = v;
    } else if (ANIMSPD(obj) < 0.0f && *(signed char *)(GetCharacterClass(obj) + 0x360) != 0) {
        v = *(float *)(w + 0x4220) = *(float *)(w + 0x4220) + ANIMSPD(obj);
        if (!(0.0f <= v))
            v = 0.0f;
        *(float *)(w + 0x4220) = v;
    }
    if (on == 0) {
        setExecRayChkPathWork(w + 0x10, 0);
    } else {
        if (*(int *)(w + 0x41C0) == 0 && *(signed char *)(GetCharacterClass(obj) + 0x35C) != 0) {
            L.e.q = L.s.q = **(s128 **)(GetLayoutClass(obj) + 0x134);
            L.e.f[1] += 10.0f;
            L.s.f[1] -= 10.0f;
            if (ClipCollisionDirect(L.hit, &L.s, &L.e, gcGlobalVar + 0x2B4) != 0)
                SetObjectGeoAndUnparent(obj, *(int *)(GetLayoutClass(obj) + 0x13C), L.hit + 0x40);
        }
        setExecRayChkPathWork(w + 0x10, 1);
    }
    found = 0;
    if (*(int *)(w + 0x4204) == 0 && *(int *)(GetLayoutClass(obj) + 0x124) != 0 && StageLayout_COMPULSION_DEATH_COLI != 0 &&
        *(int *)(StageLayout_COMPULSION_DEATH_COLI + 0x48) == GetGeometryPointerObject(GetLayoutClass(obj) + 0xC0)) {
        int pl = SCRGetFirstObj(gcGlobalVar + 0x2B0);
        if ((*(float *)(w + 0x4228) += *(float *)(gcGlobalVar + 0x180)) > 10.0f && pl != 0 &&
            ControlMode_PLAYER_DEATH != *(int *)(GetCharacterClass(pl) + 0x750) &&
            getNearPointPosUserPathWork(w + 0x10, L.hit, *(void **)(GetLayoutClass(obj) + 0x134), 2, -1) != 0) {
            found = 1;
            DebugSetObjectGeometry(obj, *(int *)(GetLayoutClass(obj) + 0x13C), L.hit);
        }
    } else {
        *(float *)(w + 0x4228) = 0;
    }
    if (on == 0 && found != 0 && *(int *)(w + 0x3B0) == 0 && *(int *)(w + 0x390) != 0) {
        if (*(int *)(getPassageWork(w + 0x10, 0) + 0x10) != 0 &&
            getPointDataByAreaIdx(w + 0x10, *(short *)(getPassageWork(w + 0x10, 0) + 0x14), *(int *)(getPassageWork(w + 0x10, 0) + 0x1C)) == 0) {
            deletePassageWork(w + 0x10, 0);
            if (*(int *)(w + 0x390) != 0) {
                do {
                    pw = getPassageWork(w + 0x10, 0);
                    if (*(int *)(pw + 0x10) == 0)
                        break;
                    if (getPointDataByAreaIdx(w + 0x10, *(short *)(pw + 0x14), *(int *)(pw + 0x1C)) != 0) {
                        SetObjectGeoAndUnparent(obj, *(int *)(GetLayoutClass(obj) + 0x13C),
                                            getPointDataByAreaIdx(w + 0x10, *(short *)(pw + 0x14), *(int *)(pw + 0x1C)));
                        break;
                    }
                    deletePassageWork(w + 0x10, 0);
                } while (*(int *)(w + 0x390) != 0);
            }
        }
        if (*(int *)(w + 0x390) != 0 && *(int *)(getPassageWork(w + 0x10, 0) + 0x10) == 0 &&
            getPathDataAddr(w + 0x10, GetStageAreaNumberByPos(getPassageWork(w + 0x10, 0))) == 0)
            setFreezeHorseCtrlWork(w + 0x3D20, 1);
    }
    updateScriptDataSystem(obj);
    *(int *)(w + 0x41C0) = on;
    setFreezeHorseCtrlWork(w + 0x3D20, 0);
}
