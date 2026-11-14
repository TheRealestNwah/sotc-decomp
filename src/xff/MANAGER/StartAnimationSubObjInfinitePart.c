/* Parked draft (~170 diffs; word count 194 vs 195, frame 0x150 vs 0xA0). Switch on type-2 (0..46): 2 func_00090D28, 4 wind, 7 camera vibration, 12 SE, 39-42 camera region, 45 func_00090DC0, 47 volume shape, 48 wind box; callee argument lists are guesses from the asm. */
#ifdef NONMATCHING
extern char *GetLayoutClass();
extern void SetGeometryPointerNodePosState();
extern int SequenceKickWind();
extern int SequenceKickWindBox();
extern int SequenceKickWindVolumeShape();
extern int add_object_animation_camera_region();
extern char IdentityQuaternion[];
extern char ZeroPoint[];
static void updateWindGeo();
static void updateVolumeShapePQSGeo();
static void updateCamVibGeo();
static void updateSEGeo();
static void update_camera_region_geometry();
static int func_00090C20();
static int func_00090DC0();
static int func_00090D28();
static int func_00090E58();
static void kickEffect();

typedef struct {
    char *a;
    char *b;
    char *c;
    char *d;
} WindParam;

#define WIND_CASE(update_args, kick)                                                       \
    {                                                                                      \
        WindParam wp;                                                                      \
        char tmp[0x30];                                                                    \
        char *layout;                                                                      \
        update_args;                                                                       \
        layout = GetLayoutClass(obj);                                                      \
        wp.a = layout + 0x1B8;                                                             \
        wp.b = layout + 0x48;                                                              \
        wp.c = layout + 0x40;                                                              \
        wp.d = layout + 0x44;                                                              \
        SetGeometryPointerNodePosState(tmp, obj, 0, IdentityQuaternion, ZeroPoint);        \
        result = kick(handle, &wp);                                                        \
    }

int StartAnimationSubObjInfinitePart(int a0, int obj, int a2, char *a3, int a4, int type, char *a6,
                                     int handle)
{
    int result = 0;
    WindParam wp;
    char tmp[0x30];
    char *layout;

    switch (type) {
    case 2:
        result = func_00090D28(obj, a3, a3, a6 + 0x10, handle, a2);
        break;
    case 4:
        WIND_CASE(updateWindGeo(obj, a3, 0, a6, handle, 1), SequenceKickWind)
        break;
    case 48:
        WIND_CASE(updateWindGeo(obj, a3, 0, a6, handle, 1), SequenceKickWindBox)
        break;
    case 47:
        WIND_CASE(updateVolumeShapePQSGeo(obj, a3, 0, a6, handle, 1, 0), SequenceKickWindVolumeShape)
        break;
    case 45:
        result = func_00090DC0(obj, a3, a3, a6 + 0x10, handle, a2);
        break;
    case 7:
        updateCamVibGeo(obj, a3, 0, a6 + 0x10, handle, 1);
        result = func_00090E58(handle, obj, 0);
        break;
    case 12:
        updateSEGeo(0, obj, a3, a3, 0, a6 + 0x10, handle, 1);
        result = func_00090C20(kickEffect, handle, obj, a3, a0, obj, 0, IdentityQuaternion, ZeroPoint);
        break;
    case 39:
    case 40:
    case 41:
    case 42:
        update_camera_region_geometry(obj, a3, 0, 0, type);
        add_object_animation_camera_region(obj, handle, type);
        break;
    }
    return result;
}
#endif
