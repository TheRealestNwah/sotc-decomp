typedef int Qword __attribute__((mode(TI)));
typedef union { Qword q; float f[4]; } Vector;
extern void ForceParentLayoutObj(void *, void *);
extern char *GetLayoutClass(void *);
extern void UpdateLayoutClassParentSimpleGeometry(void *);
extern void UpdateLayoutClassSimpleGeometry(void *, float);
extern void GetQuaternionByAxisDirZY(Vector *, Vector *, Vector *);
static inline int setGeometry(void *object, void *parent, Vector *position, Vector *quaternion)
{
    char *layout;
    if (parent) ForceParentLayoutObj(object, parent);
    layout = GetLayoutClass(object);
    (*(Vector **)(layout + 0x134))->q = position->q;
    (*(Vector **)(layout + 0x13C))->q = quaternion->q;
    if (*(void **)(layout + 0x124)) {
        ((Vector *)(layout + 0x60))->q = quaternion->q;
        ((Vector *)(layout + 0x70))->q = position->q;
        UpdateLayoutClassParentSimpleGeometry(layout);
    }
    UpdateLayoutClassSimpleGeometry(layout, 0.0f);
    return 1;
}
int SCRSetLWSGeometry(void *object, void *parent, Vector *position, Vector *quaternion)
{
    return setGeometry(object, parent, position, quaternion);
}
int SCRSetLWSGeometryWithZY(void *object, void *parent, Vector *position, Vector *z, Vector *y)
{
    Vector quaternion;
    GetQuaternionByAxisDirZY(&quaternion, z, y);
    return setGeometry(object, parent, position, &quaternion);
}
