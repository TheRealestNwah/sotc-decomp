typedef struct {
    char pad0[8];
    int status;
    char padC[4];
    long colAttr;
} CamPlaceStatus;

typedef struct {
    char pad0[0xD0];
    CamPlaceStatus placeStatus;
} CamRegion;

static inline int get_attr_kind(CamRegion *r, long *kind)
{
    CamPlaceStatus *p = &r->placeStatus;
    *kind = p->colAttr;
    if (p->status == 1) {
        *kind &= 0xF000L << 30;
        return 1;
    }
    return 0;
}

int act_look_at_ofst_cut_camera_place_status(CamRegion *r)
{
    long k;
    if (get_attr_kind(r, &k) == 1 && k == (0xB000L << 30)) return 1;
    return 0;
}
