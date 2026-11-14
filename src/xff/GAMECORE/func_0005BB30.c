/* Parked: 152 diffs, same size (156 words). Probe of up to three surface planes through func_0005ABD8 (state block {zero, ctx, saved} passed by address). Original keeps the state at sp+0x20 above the 16-byte plane at sp+0x10 and maps floats f12..f16 to f21..f25 in order. Epilogue is split into func_0005BD60. */
#ifdef NONMATCHING
typedef long long s64;
typedef struct State State;
extern char *GetGeometryPointerSurfacePlane(void *);
extern s64 nico_GetGeometryPointerAttr(void *);
extern int func_0005ABD8(void *, void *, void *, int, int, State *, void *, void *, float, float, float, float,
                         float, int, int);

typedef struct {
    char pad0[8];
    float f8;
} Slot;

typedef struct {
    char pad0[0x1C0];
    s64 d1C0;
} Owner;

typedef int Quad __attribute__((mode(TI)));

struct State {
    int zero;
    void *ctx;
    s64 saved;
};

typedef struct {
    char pad[0x40];
    Quad q;
} Geo;

int func_0005BB30(void *ctx, Geo *g1, Quad *quad, Geo *g3, int hasA, int hasB, int hasC, Slot *slot, float f0,
                  float f1, float f2, float f3, float f4, Owner *owner, int s7, int fp)
{
    int found = 0;
    State st;
    Quad plane;
    float savedF;
    State *pz = &st;

    st.ctx = ctx;
    st.zero = 0;
    savedF = slot->f8;
    st.saved = owner->d1C0;
    if (hasB != 0) {
        plane = *quad;
        found = func_0005ABD8(st.ctx, (char *)quad + 0x10, &plane, 0, hasB == 1, pz, slot, owner, f0, f1, f2, f3, f4,
                              s7, fp);
    } else if (hasA != 0) {
        plane = g1->q;
        found = func_0005ABD8(st.ctx, GetGeometryPointerSurfacePlane(g1), &plane, 0, hasA == 1, pz, slot, owner, f0, f1,
                              f2, f3, f4, s7, fp);
    }
    if (st.zero != 0)
        return 1;
    if (hasC == 0)
        return found != 0;
    {
        s64 mask = (s64)0xF800 << 20;
        s64 c1 = (s64)0xC000 << 18;
        if ((nico_GetGeometryPointerAttr(g3) & mask) == c1 ||
            (nico_GetGeometryPointerAttr(g3) & mask) == ((s64)0xA000 << 19)) {
            s64 old = owner->d1C0;
            float oldF = slot->f8;
            int same = ((nico_GetGeometryPointerAttr(g3) & mask) ^ c1) == 0;
            owner->d1C0 = st.saved;
            slot->f8 = savedF;
            plane = g3->q;
            if (func_0005ABD8(st.ctx, GetGeometryPointerSurfacePlane(g3), &plane, 1, same, pz, slot, owner, f0, f1, f2,
                              f3, f4, s7, fp) != 0)
                return 2;
            owner->d1C0 = old;
            slot->f8 = oldF;
        }
    }
    return found != 0;
}
#endif
