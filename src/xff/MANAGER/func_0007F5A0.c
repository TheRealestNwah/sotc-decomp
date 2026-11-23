/* Dispatches a geometry update to the handler for the geometry's type. */
typedef struct {
    int type;
    char pad4[0xC];
    char sub[1];
} GeoHeader;

typedef struct {
    int unk0;
    int unk4;
    int unk8;
} GeoRef;

typedef struct {
    int unk0;
    int unk4;
} GeoExtra;

typedef struct {
    char pad0[0x14];
    unsigned int flags;
} GeoOwner;

extern void kickParticle();
extern void particleOnOff();
extern void kickEffect();
extern void *GetLayoutClass(int);
extern void updateObjectGeo(int, int, int, GeoHeader *, int, int, int, float);
extern void updateDamageGeo(int, int, int, GeoHeader *, int, int, float);
extern void updateWindGeo(int, int, int, GeoHeader *, int, int, float);
extern void updateWindBoxGeo(int, int, int, GeoHeader *, int, int, float);
extern void updateVolumeShapePQSGeo(int, int, int, GeoHeader *, int, int, int, float);
extern void updateSEGeo(int, int, int, int, int, void *, int, int);
extern void updateParticleGeo(int, int, int, int, int, void *, int, int, int, int, void *, void *, float);
extern void updateParticleDissolveGeo(int, int, int, int, int, void *, int, int, int, int, void *, void *, float);
extern void updateLWSTriggerGeo(int, int, int, int, int, GeoHeader *, int, int, float);
extern void updateLightGeo(int, int, int, GeoHeader *, int, float);
extern void updateGameLightGeo(void *, GeoHeader *, int);
extern void updateClipGameLightGeo(void *, GeoHeader *, int);
extern void updateCamVibGeo(int, int, int, void *, int, int, float);
extern int update_camera_region_geometry(int, int, int, GeoHeader *, int);

static inline void cameraRegion(int obj, int target, GeoHeader *geo)
{
    update_camera_region_geometry(obj, target, 0, geo, geo->type);
}

static void func_0007F5A0(int obj, int target, GeoHeader *geo, int d, GeoRef *ref, GeoExtra *ex, int arg,
                          GeoOwner *owner, float unused, float f)
{
    switch (geo->type) {
    case 1:
    case 5:
        updateObjectGeo(obj, target, 0, geo, d, ref->unk8, (owner->flags >> 1) & 1, f);
        break;
    case 3:
    case 10:
    case 13:
        updateDamageGeo(obj, target, 0, geo, ref->unk8, geo->type, f);
        break;
    case 4:
        updateWindGeo(obj, target, 0, geo, ref->unk8, ref->unk0, f);
        break;
    case 48:
        updateWindBoxGeo(obj, target, 0, geo, ref->unk8, ref->unk0, f);
        break;
    case 47:
        updateVolumeShapePQSGeo(obj, target, 0, geo, ref->unk8, ref->unk0, 0, f);
    case 12:
        updateSEGeo(0, obj, target, target, 0, geo->sub, ref->unk8, ref->unk0);
        break;
    case 2:
        updateParticleGeo(0, obj, target, target, 0, geo->sub, d, ex->unk4, ref->unk8, ref->unk0, kickParticle,
                          particleOnOff, f);
        break;
    case 45:
        updateParticleDissolveGeo(0, obj, target, target, 0, geo->sub, d, ex->unk4, ref->unk8, ref->unk0,
                                  kickParticle, particleOnOff, f);
        break;
    case 11:
        updateParticleGeo(0, obj, target, target, 0, geo->sub, d, ex->unk4, ref->unk8, ref->unk0, kickEffect, 0, f);
        break;
    case 38:
        updateLWSTriggerGeo(0, obj, target, target, 0, geo, arg, d, f);
        break;
    case 9:
        updateLWSTriggerGeo(0, obj, target, target, 0, geo, ref->unk8, d, f);
        break;
    case 6:
        updateLightGeo(obj, target, 0, geo, ref->unk8, f);
        break;
    case 27:
    case 28:
        updateGameLightGeo(GetLayoutClass(target), geo, ex->unk4);
        break;
    case 33:
    case 34:
    case 35:
        updateClipGameLightGeo(GetLayoutClass(target), geo, ex->unk4);
        break;
    case 7:
        updateCamVibGeo(obj, target, 0, geo->sub, ref->unk8, ref->unk0, f);
        break;
    case 39:
    case 40:
    case 41:
    case 42:
        cameraRegion(obj, target, geo);
        break;
    }
}
