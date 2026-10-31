extern char IdentityQuaternion[];
extern char ZeroPoint[];
extern void SetGeometryPointerNodePosState(void *, void *, void *, void *, void *);
extern void SequenceKickCameraVibration(void *, void *);

static void func_00090E58(void *o, void *a, void *b)
{
    float m[16];

    SetGeometryPointerNodePosState(m, a, b, IdentityQuaternion, ZeroPoint);
    SequenceKickCameraVibration(o, m);
}
