typedef struct { int lo; int hi; } __attribute__((aligned(8))) CamColAttr;

typedef struct {
    char pad0[8];
    int status;
    char padC[4];
    CamColAttr colAttr;
} CamPlaceStatus;

typedef struct {
    char pad0[0x150];
    CamPlaceStatus placeStatus;
} OnBossCamera;

int get_on_boss_camera_col_attr_camera_place_status(CamColAttr *attr, OnBossCamera *camera)
{
    CamPlaceStatus *p = &camera->placeStatus;
    *attr = p->colAttr;
    return p->status;
}
