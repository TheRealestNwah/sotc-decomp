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
    char pad0[0x14];
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
