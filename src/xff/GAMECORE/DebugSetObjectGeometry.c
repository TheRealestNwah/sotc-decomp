typedef int s128 __attribute__((mode(TI)));

extern s128 ZeroVector;
extern char *GetLayoutClass(void *);
extern char *GetCharacterClass(void *);
extern void UpdateCharacterClassGeometry(char *);
extern void charrootdyn_getRegularColFinderPosition(char *, char *, void *, s128 *);
extern void UpdateCharacterClassPastGeometry(char *);
extern void SetCharacterObjDemoCutFinishFlag(void *, int);
extern void UpdateLayoutClassSimpleGeometry(char *, float);
extern void GetClothDynamics(void *, float, int, int, float);
extern void UpdateLayoutClassPastSimpleGeometry(char *);
extern void SetLayoutClassRootQuaternion(char *, void *);
extern void ForceUnparentLayoutObj(void *);
extern void CallLayoutObjDebugResetFunc(void *);
extern void ResetCharacterObj(void *);

void DebugSetObjectGeometry(void *obj, void *quat, s128 *pos)
{
    char *l;
    char *c;
    float scale;

    ForceUnparentLayoutObj(obj);
    CallLayoutObjDebugResetFunc(obj);
    scale = 100.0f;
    ResetCharacterObj(obj);
    l = GetLayoutClass(obj);

    if (l == 0)
        return;
    **(s128 **)(l + 0x134) = *pos;
    *(s128 *)(l + 0x40) = *pos;
    *(s128 *)(l + 0x30) = ZeroVector;
    c = GetCharacterClass(obj);
    if (c != 0) {
        UpdateCharacterClassGeometry(c);
        charrootdyn_getRegularColFinderPosition(c + 0x4C0, c, *(void **)(l + 0x13C), *(s128 **)(l + 0x134));
        UpdateCharacterClassPastGeometry(c);
        SetCharacterObjDemoCutFinishFlag(obj, 1);
    } else {
        UpdateLayoutClassSimpleGeometry(l, scale);
        GetClothDynamics(obj, 0.01f, 1, 0, scale);
        UpdateLayoutClassPastSimpleGeometry(l);
    }
    SetLayoutClassRootQuaternion(l, quat);
}
