/* Parked: 2 diffs with per-file -fno-strict-aliasing, same size (209 words) (82 before; 156 without the flag). Fixes: one local struct pins the frame (res +0, hit +0x40, end +0x50, mtx +0x60, slide +0xA0, dbg +0xC0), ForceAcceptMotion takes a float third argument, SlideCollisionFinder4D has an extra int argument (t0), 0x9C4 is a byte store, pi/2 is 1.5707963f, and a pointer to slide keeps it in s0. Remaining: the 0x358 test loads into v1 in the original (ours v0), and the first slide load addressing ordering at the final if. */
#ifdef NONMATCHING
typedef int Vec4 __attribute__((mode(TI)));

extern char *GetCharacterClass();
extern int GetDamageClass(int);
extern void FlushCollisionWork(int);
extern void charrootdyn_getRegularColFinderPosition(void *, void *, void *, void *);
extern void charrootdyn_getCollisionDB(void *, void *, int, void *, int, int, float);
extern int ClipCollisionFinder(void *, void *, void *, void *);
extern int SlideCollisionFinder4D(void *, int, void *, void *, int, float, float);
extern void DebugDispRadiusIndicator(void *, int, float);
extern void DebugDispLineCircle(void *, float);
extern void DebugDispCollisionDB(void *, int);
extern void glBegin(int);
extern void glEnd(void);
extern void glEnable(int);
extern void glColor4f(float, float, float, float);
extern void glLoadMatrixf(void *);
extern void glVertex3fv(void *);
extern void iosDlPushLayer(int);
extern void iosDlPopLayer(void);
extern void iosUnitMatrix(void *);
extern void iosRotMatrixX(void *, float);
extern void ForceUnparentLayoutObj(int);
extern void StabilizeToYRotQuaternion(int);
extern void ForceAcceptMotion(void *, int, float);
extern void ForceAcceptMotionControlChange(void *, int);
extern void ResetCharacterClassSyncMode(void *);
extern void ResetCharacterClassMotInterpInfo(void *);
extern void ResetCharacterClassIKInfo(void *);
extern void ResetCharacterClassFallDownInfo(void *);
extern void SetCharacterClassWindDynamics(void *, int);
extern void DebugResetCharacterObjControlTarget(int, int);
extern void ResetCharacterClassCtrlRelationInfos(void *);
extern void ResetCharacterClassDynamicsElement(void *);
extern void ResetCharacterClassSlideStatus(void *);
extern void ResetCharacterClassPositionMemoryInfo(void *);
extern void ResetCharacterClassWaterStatus(void *);
extern void ResetCharacterClassMotionInterpRootOfs(void *);
extern void ResetCharacterObjGeoDynamics(int);
extern void ResetDamageClass(int);
extern void CallLayoutObjDebugResetFunc(int);
extern void GetCharaVCollisionStatus(void *);
extern void charrootdyn_getChainStatus(int);
extern char UnitMatrix[];

#define F(c, o) (*(float *)((c) + (o)))
#define I(c, o) (*(int *)((c) + (o)))
#define P(c, o) (*(char **)((c) + (o)))

void func_00000218(int obj)
{
    Vec4 *sp;
    char *c = GetCharacterClass();
    int dmg = GetDamageClass(obj);
    char *db;
    int *q = (int *)(c + 0x1C0);
    struct { char res[0x40]; Vec4 hit; Vec4 end; char mtx[0x40]; Vec4 slide; Vec4 pad; char dbg[0x60]; } L;

    FlushCollisionWork(obj);
    if (*(int *)(c + 0x358)) {
        char *pos = c + 0x4C0;
        db = c + 0xE20;
        charrootdyn_getRegularColFinderPosition(pos, c, P(c, 0x13C), P(c, 0x134));
        charrootdyn_getCollisionDB(db, (char *)I(c, 0xE38) + *(short *)(c + 0x370) * 4, obj, pos, (int)(c + 0x4D0), *q, F(c, 0xE34));
    } else {
        db = c + 0xE20;
        charrootdyn_getCollisionDB(db, (char *)I(c, 0xE38) + *(short *)(c + 0x370) * 4, obj, P(c, 0x134), I(c, 0x138), *q, F(c, 0xE34));
    }
    L.end = *(Vec4 *)P(c, 0x134);
    ((float *)&L.end)[1] -= F(c, 0xE34);
    if (ClipCollisionFinder(L.res, P(c, 0x134), &L.end, db) != 0) {
        L.end = L.hit;
        glEnable(7);
        DebugDispRadiusIndicator(&L.hit, 1, 0.05f);
        glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
        iosUnitMatrix(L.mtx);
        iosRotMatrixX(L.mtx, 1.5707963f);
        *(Vec4 *)(L.mtx + 0x30) = L.hit;
        DebugDispLineCircle(L.mtx, 1.0f);
    } else {
        glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
    }
    glEnable(3);
    glLoadMatrixf(UnitMatrix);
    iosDlPushLayer(0x17);
    glBegin(1);
    glVertex3fv(P(c, 0x134));
    glVertex3fv(&L.end);
    glEnd();
    iosDlPopLayer();
    ForceUnparentLayoutObj(obj);
    StabilizeToYRotQuaternion(I(c, 0x13C));
    ForceAcceptMotion(c, I(c, 0x2AC), 0.0f);
    ForceAcceptMotionControlChange(c, I(c, 0x2B0));
    *(Vec4 *)(c + 0x1150) = *(Vec4 *)P(c, 0x134);
    F(c, 0x1154) = F(c, 0x1154) - F(c, 0x394);
    ResetCharacterClassSyncMode(c);
    ResetCharacterClassMotInterpInfo(c);
    ResetCharacterClassIKInfo(c);
    ResetCharacterClassFallDownInfo(c);
    SetCharacterClassWindDynamics(c, 0);
    DebugResetCharacterObjControlTarget(obj, obj);
    ResetCharacterClassCtrlRelationInfos(c);
    ResetCharacterClassDynamicsElement(c);
    ResetCharacterClassSlideStatus(c);
    ResetCharacterClassPositionMemoryInfo(c);
    ResetCharacterClassWaterStatus(c);
    ResetCharacterClassMotionInterpRootOfs(c);
    ResetCharacterObjGeoDynamics(obj);
    ResetDamageClass(dmg);
    CallLayoutObjDebugResetFunc(obj);
    *(char *)(c + 0x9C4) = 1;
    sp = &L.slide;
    if (SlideCollisionFinder4D(sp, I(c, 0x138), P(c, 0x134), db, 0, F(c, 0xE0C), 0.01f) != 0) {
        *(Vec4 *)P(c, 0x134) = *sp;
        DebugDispRadiusIndicator(sp, 1, 0.1f);
        DebugDispCollisionDB(L.dbg, 0);
    }
    GetCharaVCollisionStatus(c);
    charrootdyn_getChainStatus(obj);
}
#endif
