typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;

extern const float RO_0017F670;
extern int ScriptCtrlDef_SCRPlayerBackDirectionHang;
extern int ScriptCtrlDef_SCRPlayerFrontDirectionHang;
extern int ScriptCtrlDef_SCRPlayerRightDirectionHang;
extern int ScriptCtrlDef_SCRPlayerLeftDirectionHang;
extern int ScriptCtrlDef_SCRPlayerDownDirectionHang;
extern int ScriptCtrlDef_SCRPlayerUpDirectionHang;
extern void GetGeometryPointerPosition(Vec4 *, void *);
extern int SCRGetCollision(void *, Vec4 *, Vec4 *, void *);
extern int charrootdyn_detectCharClimbableWall(void *, void *, int, Vec4 *, float, float, float, float, Vec4 *, void *);
extern long nico_GetGeometryPointerAttr(void *);

static inline int isAttr4(void *geo) { long a = nico_GetGeometryPointerAttr(geo) & 4; return a != 0; }
static inline int isAttr1(void *geo) { return nico_GetGeometryPointerAttr(geo) & 1; }
static inline int notAttr2(void *geo) { long a = nico_GetGeometryPointerAttr(geo) & 2; return a == 0; }

static inline int isClimb(void *geo)
{
    int r = 0;
    if (isAttr4(geo) || (isAttr1(geo) && notAttr2(geo)))
        r = 1;
    return r;
}

static inline int isHigher(float y, float *best)
{
    if (y < *best) {
        *best = y;
        return 1;
    }
    return 0;
}

int tryToCheckCollision6Dir(void *geo, Vec4 *pos, Vec4 *vec, char *work, Vec4 *src, Vec4 *tbl, void *extra,
                            float off)
{
    char buf[0xA0];
    Vec4 copy;
    Vec4 p;
    float best = RO_0017F670;
    float y;

    vec->q = src->q;
    y = vec->f[1] + off;
    vec->f[1] = y;
    tbl[0].f[1] = y;
    tbl[1].f[1] = y;
    tbl[2].f[1] = y;
    tbl[3].f[1] = y;
    tbl[4].f[1] = y;
    tbl[5].f[1] = y;
    if (SCRGetCollision(geo, vec, &tbl[5], extra)) {
        int ok;
        GetGeometryPointerPosition(pos, geo);
        copy.q = pos->q;
        if (charrootdyn_detectCharClimbableWall(buf, geo, 1, &copy, 100.0f, *(float *)(work + 0xE34), 0.5f, 0.0f, vec,
                                                work + 0xE20))
            ok = 1;
        else
            ok = isClimb(geo);
        if (ok) {
            GetGeometryPointerPosition(&p, geo);
            if (isHigher(-p.f[1], &best))
                return ScriptCtrlDef_SCRPlayerBackDirectionHang;
        }
    }
    if (SCRGetCollision(geo, vec, &tbl[4], extra)) {
        int ok;
        GetGeometryPointerPosition(pos, geo);
        copy.q = pos->q;
        if (charrootdyn_detectCharClimbableWall(buf, geo, 1, &copy, 100.0f, *(float *)(work + 0xE34), 0.5f, 0.0f, vec,
                                                work + 0xE20))
            ok = 1;
        else
            ok = isClimb(geo);
        if (ok) {
            GetGeometryPointerPosition(&p, geo);
            if (isHigher(-p.f[1], &best))
                return ScriptCtrlDef_SCRPlayerFrontDirectionHang;
        }
    }
    if (SCRGetCollision(geo, vec, &tbl[3], extra)) {
        int ok;
        GetGeometryPointerPosition(pos, geo);
        copy.q = pos->q;
        if (charrootdyn_detectCharClimbableWall(buf, geo, 1, &copy, 100.0f, *(float *)(work + 0xE34), 0.5f, 0.0f, vec,
                                                work + 0xE20))
            ok = 1;
        else
            ok = isClimb(geo);
        if (ok) {
            GetGeometryPointerPosition(&p, geo);
            if (isHigher(-p.f[1], &best))
                return ScriptCtrlDef_SCRPlayerRightDirectionHang;
        }
    }
    if (SCRGetCollision(geo, vec, &tbl[2], extra)) {
        int ok;
        GetGeometryPointerPosition(pos, geo);
        copy.q = pos->q;
        if (charrootdyn_detectCharClimbableWall(buf, geo, 1, &copy, 100.0f, *(float *)(work + 0xE34), 0.5f, 0.0f, vec,
                                                work + 0xE20))
            ok = 1;
        else
            ok = isClimb(geo);
        if (ok) {
            GetGeometryPointerPosition(&p, geo);
            if (isHigher(-p.f[1], &best))
                return ScriptCtrlDef_SCRPlayerLeftDirectionHang;
        }
    }
    if (SCRGetCollision(geo, vec, &tbl[1], extra)) {
        int ok;
        GetGeometryPointerPosition(pos, geo);
        copy.q = pos->q;
        if (charrootdyn_detectCharClimbableWall(buf, geo, 1, &copy, 100.0f, *(float *)(work + 0xE34), 0.5f, 0.0f, vec,
                                                work + 0xE20))
            ok = 1;
        else
            ok = isClimb(geo);
        if (ok) {
            GetGeometryPointerPosition(&p, geo);
            if (isHigher(-p.f[1], &best))
                return ScriptCtrlDef_SCRPlayerDownDirectionHang;
        }
    }
    if (SCRGetCollision(geo, vec, &tbl[0], extra)) {
        int ok;
        GetGeometryPointerPosition(pos, geo);
        copy.q = pos->q;
        if (charrootdyn_detectCharClimbableWall(buf, geo, 1, &copy, 100.0f, *(float *)(work + 0xE34), 0.5f, 0.0f, vec,
                                                work + 0xE20))
            ok = 1;
        else
            ok = isClimb(geo);
        if (ok) {
            GetGeometryPointerPosition(&p, geo);
            if (isHigher(-p.f[1], &best))
                return ScriptCtrlDef_SCRPlayerUpDirectionHang;
        }
    }
    return 0;
}
