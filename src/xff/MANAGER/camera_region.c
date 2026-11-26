/* Camera regions: layout regions that switch the camera when the player is
 * inside them, with their metadata getters and debug display. */

typedef int s128 __attribute__((mode(TI)));
typedef struct {
    float v[4];
} __attribute__((aligned(16))) Vec4;

typedef union {
    s128 q;
    struct {
        float x, y, z, w;
    } f;
} QVec;

typedef struct {
    char pad[0x90];
    QVec scale;
} LayoutClass;

typedef struct {
    int unk0;
    int objectId;
    int parentKind; /* 1 or 2: the parent object is a boss */
    int kind;       /* 10000 always clear, 10001 clear once the parent is behind the camera */
    int priority;
    float hitOffset;
    float changeGraceTime;
} CameraRegionMetadata;

typedef struct {
    int type;
    int shape;
    long unk8;
    void *object;
    CameraRegionMetadata *metadata;
    char pad18[8];
    Vec4 region;
} CameraRegion;

static inline void vecAddXYZ(Vec4 *out, Vec4 *a, Vec4 *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vadd.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline void vecSubXYZ(float *out, float *a, float *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline float vecDot(float *a, float *b)
{
    float dot;

    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vaddw.x vf7, vf0, vf0w\n"
                         "vmul.xyz vf6, vf5, vf6\n"
                         "vaddax.x ACC, vf0, vf6x\n"
                         "vmadday.x ACC, vf7, vf6y\n"
                         "vmaddz.x vf6, vf7, vf6z\n"
                         "qmfc2.ni $2, vf6\n"
                         "mtc1 $2, %0\n"
                         : "=f"(dot) : "r"(a), "r"(b) : "$2");
    return dot;
}

#define VU_QUAT_MUL(dst, a, b) \
    __asm__ __volatile__("lqc2 vf11, 0x0(%0)\n" \
                         "lqc2 vf12, 0x0(%1)\n" \
                         "vmul.xyzw vf13, vf11, vf12\n" \
                         "vaddy.x vf13, vf13, vf13y\n" \
                         "vaddz.x vf13, vf13, vf13z\n" \
                         "vsubx.w vf13, vf13, vf13x\n" \
                         "vmulw.xyz vf14, vf12, vf11w\n" \
                         "vmulw.xyz vf15, vf11, vf12w\n" \
                         "vopmula.xyz ACC, vf12, vf11\n" \
                         "vopmsub.xyz vf16, vf11, vf12\n" \
                         "vadd.xyz vf13, vf14, vf15\n" \
                         "vadd.xyz vf13, vf13, vf16\n" \
                         "sqc2 vf13, 0x0(%2)\n" \
                         : : "r"(a), "r"(b), "r"(dst) : "memory")

extern char *GetLayoutClass(void *);
extern char *GetCharacterClass(void *);
extern void *GetLayoutParentObj(char *);
extern float *get_camera_direction(void *);
extern void *iosMallocAlign(void *, int, int);
extern void iosFree(void *);
extern void DivQuaternion(Vec4 *, Vec4 *, Vec4 *);
extern int IsInsideOfRegion(int, float *, void *, Vec4 *, float, float, float);
extern int GAMEUTIL_is_nearly_equal_zero3D(QVec *, float);
extern void DEBUG_disp_region_object(int, void *, Vec4 *, Vec4 *, void *, float, float, float);
extern void glDrawNull(float, void *, Vec4 *, void *);
extern void glDrawLineArrow(void *, Vec4 *, Vec4 *, void *, float, float);

int is_parent_obj_boss_camera_region(CameraRegion *region);
int is_have_region_camera_region(CameraRegion *region);
static void func_000E86C8(CameraRegion *p, int type, int shape, long unk8, void *object, CameraRegionMetadata *metadata);

int get_view_matrix(int arg0)
{
    return arg0 + 0x210;
}

/* Whether pos is inside the region, grown by the hit offset when other is a
 * region of the same object. */
static int func_000E7D48(float *pos, char *layout, CameraRegion *region, CameraRegion *other)
{
    int inside = 0;
    if (is_have_region_camera_region(region) == 1) {
        CameraRegionMetadata *meta = region->metadata;
        Vec4 center;
        if (other != 0 && region->object == other->object) {
            Vec4 offset;
            Vec4 tmp;
            tmp.v[0] = meta->hitOffset;
            tmp.v[1] = meta->hitOffset;
            tmp.v[2] = meta->hitOffset;
            tmp.v[3] = 0.0f;
            offset = tmp;
            vecAddXYZ(&center, (Vec4 *)(layout + 0x90), &offset);
        } else {
            *(s128 *)&center = *(s128 *)(layout + 0x90);
        }
        switch (region->shape) {
        case 0x27:
            inside = IsInsideOfRegion(0, pos, *(void **)(layout + 0x134), &region->region, center.v[0], center.v[1], center.v[2]);
            break;
        case 0x28:
            inside = IsInsideOfRegion(3, pos, *(void **)(layout + 0x134), &region->region, center.v[0], center.v[1], center.v[2]);
            break;
        case 0x29:
            inside = IsInsideOfRegion(2, pos, *(void **)(layout + 0x134), &region->region, 2.0f, center.v[0], center.v[1]);
            break;
        case 0x2A:
            inside = IsInsideOfRegion(1, pos, *(void **)(layout + 0x134), &region->region, center.v[0], center.v[1], center.v[2]);
            break;
        }
    }
    return inside;
}

void disp_camera_region(CameraRegion *region, void *mode, int count, float alpha)
{
    if (is_have_region_camera_region(region) == 1) {
        Vec4 *rot = &region->region;
        float colors[3][4] __attribute__((aligned(16))) = { { 0.0f, 1.0f, 1.0f, alpha }, { 1.0f, 0.2f, 0.2f, alpha }, { 0.2f, 1.0f, 0.2f, alpha } };
        char *layout;
        Vec4 dir;
        int i;

        layout = GetLayoutClass(region->object);
        __asm__ __volatile__("lqc2 vf4, 0x0(%1)\n"
                             "vmul.xyzw vf5, vf4, vf4\n"
                             "vmr32.xyzw vf6, vf4\n"
                             "vmul.xyzw vf7, vf6, vf4\n"
                             "vmr32.xyzw vf6, vf6\n"
                             "vmul.xyzw vf8, vf6, vf4\n"
                             "vsubx.z vf6, vf0, vf5x\n"
                             "vsuby.z vf6, vf6, vf5y\n"
                             "vaddw.y vf6, vf7, vf7w\n"
                             "vsuby.x vf6, vf8, vf8y\n"
                             "vsub.w vf6, vf0, vf0\n"
                             "vadd.w vf5, vf0, vf0\n"
                             "vmulw.xyz vf6, vf6, vf5w\n"
                             "vaddw.z vf6, vf6, vf0w\n"
                             "sqc2 vf6, 0x0(%0)\n"
                             : : "r"(&dir), "r"(rot) : "memory");
        if (count > 2)
            count = 2;
        for (i = 0; i < count; i++) {
            Vec4 color;
            Vec4 center;
            if (i == 0)
                *(s128 *)&color = *(s128 *)&colors[0];
            else
                *(s128 *)&color = *(s128 *)&colors[1];
            if (i == 0) {
                *(s128 *)&center = *(s128 *)(layout + 0x90);
            } else {
                CameraRegionMetadata *meta = region->metadata;
                Vec4 offset;
                Vec4 tmp;
                tmp.v[0] = meta->hitOffset;
                tmp.v[1] = meta->hitOffset;
                tmp.v[2] = meta->hitOffset;
                tmp.v[3] = 0.0f;
                offset = tmp;
                vecAddXYZ(&center, (Vec4 *)(layout + 0x90), &offset);
            }
            switch (region->shape) {
            case 0x27:
                DEBUG_disp_region_object(0, *(void **)(layout + 0x134), rot, &color, mode, center.v[0], center.v[1], center.v[2]);
                break;
            case 0x28:
                DEBUG_disp_region_object(3, *(void **)(layout + 0x134), rot, &color, mode, center.v[0], center.v[1], center.v[2]);
                break;
            case 0x29:
                DEBUG_disp_region_object(2, *(void **)(layout + 0x134), rot, &color, mode, 2.0f, center.v[0], center.v[1]);
                break;
            case 0x2A:
                DEBUG_disp_region_object(1, *(void **)(layout + 0x134), rot, &color, mode, center.v[0], center.v[1], center.v[2]);
                break;
            }
        }
        if (count > 0) {
            glDrawNull(0.3f, *(void **)(layout + 0x134), (Vec4 *)colors[2], mode);
            glDrawLineArrow(*(void **)(layout + 0x134), &dir, (Vec4 *)colors[2], mode, 1.0f, 0.5f);
        }
    }
}

void constructor_camera_region(CameraRegion *r)
{
    r->type = -1;
    r->shape = 0;
    r->unk8 = 0;
    r->object = 0;
    r->metadata = 0;
    __asm__ __volatile__(".set noreorder\n"
                         "sqc2 vf0, 0x0(%0)\n"
                         ".set reorder\n"
                         : : "r"(&r->region) : "memory");
}

CameraRegion *create_and_init_camera_region(int type, int shape, long unk8, void *object, CameraRegionMetadata *metadata, void *heap)
{
    CameraRegion *region = iosMallocAlign(heap, sizeof(CameraRegion), 0x10);
    func_000E86C8(region, type, shape, unk8, object, metadata);
    return region;
}

void check_free_camera_region(void **arg0)
{
    void *temp_v0;

    temp_v0 = *arg0;
    if (temp_v0 != 0) {
        iosFree(temp_v0);
        *arg0 = 0;
    }
}

/* Follows the layout's rotation, and a boss parent's when it has one. */
void doit_camera_region(CameraRegion *r, void *obj, float t)
{
    char *layout = GetLayoutClass(r->object);
    *(s128 *)&r->region = **(s128 **)(layout + 0x13C);
    if (obj != 0 && is_parent_obj_boss_camera_region(r) == 1) {
        char *parent = GetLayoutClass(obj);
        *(int *)(layout + 0x1AC) = *(int *)(parent + 0x1AC);
        /* read as an int: the int store above may alias it, so it isn't hoisted */
        if (((CameraRegionMetadata *)*(int *)&r->metadata)->parentKind == 2) {
            Vec4 q;
            DivQuaternion(&q, &r->region, *(Vec4 **)(parent + 0x13C));
            VU_QUAT_MUL(&r->region, GetCharacterClass(obj) + 0x470, &q);
        }
    }
}

int is_clear_camera_region_condition(float *pos, CameraRegion *region, void *arg, void *camera, int boss)
{
    int clear = 0;
    char *layout = GetLayoutClass(region->object);
    void *parent;
    float diff[4];

    if (!is_parent_obj_boss_camera_region(region) || boss == 1) {
        if (func_000E7D48(pos, layout, region, arg) == 1) {
            int kind = region->metadata->kind;
            if (kind == 10000) {
                clear = 1;
            } else if (kind == 10001) {
                parent = GetLayoutParentObj(layout);
                if (parent != 0) {
                    vecSubXYZ(diff, *(float **)(GetLayoutClass(parent) + 0x134), pos);
                    if (vecDot(diff, get_camera_direction(camera)) <= 0.0f)
                        clear = 1;
                }
            }
        }
    }
    return clear;
}

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

static inline int getType(CameraRegion *region)
{
    if (hasMetadata(region)) {
        return region->type;
    }
    return -1;
}

int is_have_region_camera_region(CameraRegion *region)
{
    QVec v;
    if (getType(region) == 0) {
        v.q = ((LayoutClass *)GetLayoutClass(region->object))->scale.q;
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

static void func_000E86C8(CameraRegion *p, int type, int shape, long unk8, void *object, CameraRegionMetadata *metadata)
{
    p->type = type;
    p->shape = shape;
    p->unk8 = unk8;
    p->object = object;
    p->metadata = metadata;
}
