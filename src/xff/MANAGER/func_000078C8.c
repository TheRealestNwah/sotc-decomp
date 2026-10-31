extern void *GetCharacterClass(void *);
extern void *GetLayoutClass(void *);
extern void SetCharacterClassRootQuaternionWithInterpolationGeometry(void *, void *);
extern void SetLayoutClassRootQuaternion(void *, void *);

static void func_000078C8(void *obj, void *quat)
{
    void *cls = GetCharacterClass(obj);

    if (cls != 0) {
        SetCharacterClassRootQuaternionWithInterpolationGeometry(cls, quat);
    } else {
        cls = GetLayoutClass(obj);
        if (cls != 0) {
            SetLayoutClassRootQuaternion(cls, quat);
        }
    }
}
