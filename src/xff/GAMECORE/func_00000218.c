/* Parked: 156 diffs, same size (207 words). Debug character reset: collision DB probe, line draw, then ~20 Reset and Set calls. All logic matches; remaining diffs are stack slot placement (original: ClipCollisionFinder result at sp+0 with hit at +0x40, end at +0x50, matrix +0x60, slide +0xA0, debug +0xC0, frame 0x160 vs 0x150) and the s3 = &c->x1C0 base kept across the first calls. */
#ifdef NONMATCHING
typedef int Vec4 __attribute__((mode(TI)));

extern char *GetCharacterClass();
extern int GetDamageClass(int);
extern void FlushCollisionWork(int);
extern void charrootdyn_getRegularColFinderPosition(void *, void *, void *, void *);
extern void charrootdyn_getCollisionDB(void *, void *, int, void *, int, int, float);
extern int ClipCollisionFinder(void *, void *, void *, void *);
extern int SlideCollisionFinder4D(void *, int, void *, void *, float, float);
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
extern void ForceAcceptMotion(void *, int, int);
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
    char *c = GetCharacterClass();
    int dmg = GetDamageClass(obj);
    char *db;
    int *q = (int *)(c + 0x1C0);
    char dbg[0x60];
    Vec4 slide;
    char mtx[0x40];
    Vec4 end;
    Vec4 hit;
    char res[0x40];

    FlushCollisionWork(obj);
    if (I(c, 0x358) != 0) {
        char *pos = c + 0x4C0;
        db = c + 0xE20;
        charrootdyn_getRegularColFinderPosition(pos, c, P(c, 0x13C), P(c, 0x134));
        charrootdyn_getCollisionDB(db, (char *)I(c, 0xE38) + *(short *)(c + 0x370) * 4, obj, pos, (int)(c + 0x4D0), *q, F(c, 0xE34));
    } else {
        db = c + 0xE20;
        charrootdyn_getCollisionDB(db, (char *)I(c, 0xE38) + *(short *)(c + 0x370) * 4, obj, P(c, 0x134), I(c, 0x138), *q, F(c, 0xE34));
    }
    end = *(Vec4 *)P(c, 0x134);
    ((float *)&end)[1] -= F(c, 0xE34);
    if (ClipCollisionFinder(res, P(c, 0x134), &end, db) != 0) {
        end = hit;
        glEnable(7);
        DebugDispRadiusIndicator(&hit, 1, 0.05f);
        glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
        iosUnitMatrix(mtx);
        iosRotMatrixX(mtx, 1.5707964f);
        *(Vec4 *)(mtx + 0x30) = hit;
        DebugDispLineCircle(mtx, 1.0f);
    } else {
        glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
    }
    glEnable(3);
    glLoadMatrixf(UnitMatrix);
    iosDlPushLayer(0x17);
    glBegin(1);
    glVertex3fv(P(c, 0x134));
    glVertex3fv(&end);
    glEnd();
    iosDlPopLayer();
    ForceUnparentLayoutObj(obj);
    StabilizeToYRotQuaternion(I(c, 0x13C));
    ForceAcceptMotion(c, I(c, 0x2AC), 0);
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
    I(c, 0x9C4) = 1;
    if (SlideCollisionFinder4D(&slide, I(c, 0x138), P(c, 0x134), db, F(c, 0xE0C), 0.01f) != 0) {
        *(Vec4 *)P(c, 0x134) = slide;
        DebugDispRadiusIndicator(&slide, 1, 0.1f);
        DebugDispCollisionDB(dbg, 0);
    }
    GetCharaVCollisionStatus(c);
    charrootdyn_getChainStatus(obj);
}
#endif
