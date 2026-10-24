typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; int i[4]; } Vec4;
typedef struct { Vec4 geometry[5]; int mode; } ParentRequest;
extern void *GetCharacterClass(void *);
extern void SetGeometryPointerNodePosState(Vec4 *, int, int, Vec4 *, Vec4 *);
extern int ForceParentLayoutObj(void *, void *);
extern char *GetLayoutClass(unsigned char *);
extern Vec4 IdentityQuaternion;
extern Vec4 ZeroPoint;

int SendCharaNodeParentSetMsg(void *object, void *parent, int node)
{
    ParentRequest request;
    if (GetCharacterClass(object)) {
        char *layout;
        request.mode = 4;
        SetGeometryPointerNodePosState(request.geometry, (int)parent, node,
            &IdentityQuaternion, &ZeroPoint);
        ForceParentLayoutObj(object, &request);
        layout = GetLayoutClass(object);
        ((Vec4 *)(layout + 0x70))->q = ZeroPoint.q;
        ((Vec4 *)(layout + 0x60))->q = IdentityQuaternion.q;
        return 1;
    }
    return 0;
}
