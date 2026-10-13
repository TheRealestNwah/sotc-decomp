typedef struct LayoutObj LayoutObj;

extern void ForceUnparentLayoutObj(LayoutObj *obj);
extern void CallLayoutObjDebugResetFunc(LayoutObj *obj);
extern void ResetCharacterObj(LayoutObj *obj);

void ResetObject(LayoutObj *obj)
{
    ForceUnparentLayoutObj(obj);
    CallLayoutObjDebugResetFunc(obj);
    ResetCharacterObj(obj);
}
