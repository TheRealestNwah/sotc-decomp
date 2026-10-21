typedef struct {
    int unk0;
    int objectId;
    int parentKind;
    int unkC;
    int priority;
    float hitOffset;
    float changeGraceTime;
} CameraRegionMetadata;

typedef struct {
    int type;
    char pad4[0xC];
    void *unk10;
    CameraRegionMetadata *metadata;
} CameraRegion;

static inline int hasMetadata(CameraRegion *region)
{
    if (region != 0 && region->metadata != 0) {
        return 1;
    }
    return 0;
}

int get_manage_object_id_camera_region(CameraRegion *region)
{
    if (hasMetadata(region)) {
        return region->metadata->objectId;
    }
    return -1;
}

int is_parent_obj_boss_camera_region(CameraRegion *region)
{
    if (hasMetadata(region) == 1) {
        if (region->metadata->parentKind == 1 || region->metadata->parentKind == 2) {
            return 1;
        }
    }
    return 0;
}

int get_priority_camera_region(CameraRegion *region)
{
    if (hasMetadata(region)) {
        return region->metadata->priority;
    }
    return 0;
}

float get_change_grace_time_camera_region(CameraRegion *region)
{
    if (hasMetadata(region)) {
        return region->metadata->changeGraceTime;
    }
    return 0.0f;
}

float get_hit_region_ofst_camera_region(CameraRegion *region)
{
    if (hasMetadata(region)) {
        return region->metadata->hitOffset;
    }
    return 0.0f;
}

int get_region_type_camera_region(CameraRegion *region)
{
    if (hasMetadata(region)) {
        return region->type;
    }
    return -1;
}

typedef int s128 __attribute__((mode(TI)));
typedef union {
    s128 q;
    struct {
        float x, y, z, w;
    } f;
} Vec4;
typedef struct {
    char pad[0x90];
    Vec4 scale;
} LayoutClass;
typedef struct {
    int a;
    int b;
    long c;
    int d;
    int e;
} CameraRegionInit;

extern LayoutClass *GetLayoutClass(void *);
extern int GAMEUTIL_is_nearly_equal_zero3D(Vec4 *, float);
extern CameraRegion *B_0015E350[50];
extern int D_00139F4C;
extern int D_00139F50;
extern int rootPtn;
extern void *memset(void *, int, unsigned int);
extern void doit_camera_region(CameraRegion *, void *, float);
extern CameraRegion *create_and_init_camera_region(int, void *, int, void *, void *, void *);
extern void check_free_camera_region(CameraRegion **);

static inline int getType(CameraRegion *region)
{
    if (hasMetadata(region)) {
        return region->type;
    }
    return -1;
}

int is_have_region_camera_region(CameraRegion *region)
{
    Vec4 v;
    if (getType(region) == 0) {
        v.q = GetLayoutClass(region->unk10)->scale.q;
        if (v.f.x < 0.0f) {
            v.f.x = 0.0f;
        }
        if (v.f.y < 0.0f) {
            v.f.y = 0.0f;
        }
        if (v.f.z < 0.0f) {
            v.f.z = 0.0f;
        }
        if (!GAMEUTIL_is_nearly_equal_zero3D(&v, 0.001f)) {
            return 1;
        }
    }
    return 0;
}

static void func_000E86C8(CameraRegionInit *p, int a, int b, long c, int d, int e)
{
    p->a = a;
    p->b = b;
    p->c = c;
    p->d = d;
    p->e = e;
}

void init_camera_region_manager(void)
{
    memset(B_0015E350, 0, sizeof(B_0015E350));
}

void doit_camera_region_manager(void *arg, float t)
{
    int i;
    for (i = 0; i < 50; i++) {
        if (B_0015E350[i] != 0) {
            doit_camera_region(B_0015E350[i], arg, t);
        }
    }
}

int add_object_animation_camera_region(void *obj, void *a1, void *a2)
{
    int i;
    if (obj != 0 && a1 != 0) {
        for (i = 0; i < 50; i++) {
            if (B_0015E350[i] == 0) {
                B_0015E350[i] = create_and_init_camera_region(0, a2, 0, obj, a1, &rootPtn);
                return 1;
            }
        }
    }
    return 0;
}

int delete_object_animation_camera_region(void *obj)
{
    int i;
    if (obj != 0) {
        for (i = 0; i < 50; i++) {
            if (B_0015E350[i] != 0 && B_0015E350[i]->unk10 == obj) {
                check_free_camera_region(&B_0015E350[i]);
                return 1;
            }
        }
    }
    return 0;
}

int get_max_object_animation_camera_region(void)
{
    return 50;
}

int get_cur_total_object_animation_camera_region(void)
{
    int i;
    int n = 0;
    for (i = 0; i < 50; i++) {
        if (B_0015E350[i] != 0) {
            n++;
        }
    }
    return n;
}

int *get_col_attr_cam_region_select_flag(void)
{
    return &D_00139F4C;
}

int *get_col_attr_cam_region_select_index(void)
{
    return &D_00139F50;
}
