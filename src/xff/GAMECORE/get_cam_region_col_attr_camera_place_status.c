typedef struct { int lo; int hi; } __attribute__((aligned(8))) CamColAttr;

typedef struct {
    char pad0[8];
    int status;
    char padC[4];
    CamColAttr colAttr;
} CamPlaceStatus;

typedef struct {
    char pad0[0xD0];
    CamPlaceStatus placeStatus;
} CamRegion;

int get_cam_region_col_attr_camera_place_status(CamColAttr *attr, CamRegion *region)
{
    CamPlaceStatus *p = &region->placeStatus;
    *attr = p->colAttr;
    return p->status;
}
