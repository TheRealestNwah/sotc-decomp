extern int *DldSysUndefSymbol;
extern char *GetCharacterClass(void *);
extern void DebugCallCharacterObjMotionLeaveFunc(void *);
extern void ForceAcceptMotion(void *, int, float);
extern void ForceAcceptMotionControlChange(void *, void *);
extern void ResetCharacterClassSyncMode(void *);
extern void ResetCharacterClassMotInterpInfo(void *);
extern void ResetCharacterClassIKInfo(void *);
extern void ResetCharacterClassFallDownInfo(void *);
extern void SetCharacterClassWindDynamics(void *, int);
extern void DebugResetCharacterObjControlTarget(void *, void *);
extern void ResetCharacterClassCtrlRelationInfos(void *);
extern void ResetCharacterClassDynamicsElement(void *);
extern void ResetCharacterClassSlideStatus(void *);
extern void ResetCharacterClassPositionMemoryInfo(void *);
extern void ResetCharacterClassWaterStatus(void *);
extern void ResetCharacterClassMotionInterpRootOfs(void *);
extern void ReleaseCharacterClassMotSyncAnim(void *);
extern void *GetDamageClass(void *);
extern void ResetDamageClass(void *);

static inline char *dldResolve(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;

    return (t != 0 && t != DldSysUndefSymbol) ? (char *)t[4] + ((v >> 18) & 0xFFF) * ((int *)t[2])[3] : 0;
}

void ResetCharacterObj(void *obj)
{
    char *cc = GetCharacterClass(obj);
    char *ctrl;

    if (cc == 0)
        return;
    if (dldResolve((unsigned int *)(*(char **)(cc + 0x1140) + 0xEC)) != 0)
        ctrl = dldResolve((unsigned int *)(*(char **)(cc + 0x1140) + 0xEC));
    else
        ctrl = *(char **)(cc + 0x2B0);
    DebugCallCharacterObjMotionLeaveFunc(obj);
    ForceAcceptMotion(cc, *(int *)(cc + 0x2AC), 0.0f);
    ForceAcceptMotionControlChange(cc, ctrl);
    ResetCharacterClassSyncMode(cc);
    ResetCharacterClassMotInterpInfo(cc);
    ResetCharacterClassIKInfo(cc);
    ResetCharacterClassFallDownInfo(cc);
    SetCharacterClassWindDynamics(cc, 0);
    DebugResetCharacterObjControlTarget(obj, obj);
    ResetCharacterClassCtrlRelationInfos(cc);
    ResetCharacterClassDynamicsElement(cc);
    ResetCharacterClassSlideStatus(cc);
    ResetCharacterClassPositionMemoryInfo(cc);
    ResetCharacterClassWaterStatus(cc);
    ResetCharacterClassMotionInterpRootOfs(cc);
    ReleaseCharacterClassMotSyncAnim(obj);
    *(char *)(cc + 0x52A) = 5;
    ResetDamageClass(GetDamageClass(obj));
}
