typedef struct ClipVisual {
    char pad0[0x8];
    struct { char pad0[0x3C]; int unk3C; } *unk8;
    char padC[0xC];
    int unk18;
} ClipVisual;

typedef struct ClipCamera {
    char pad0[0xC];
    float unkC;
} ClipCamera;

typedef struct ClipObj {
    struct { char pad0[0x20]; ClipVisual *unk20; } *unk0;
    char pad4[0x1C];
    float unk20;
    float unk24;
    float unk28;
    char pad2C[0x4];
    float unk30;
    float unk34;
    char pad38[0x64];
    float unk9C;
    char padA0[0xA0];
    struct ClipObj *unk140;
    struct ClipObj *unk144;
    char pad148[0x14];
    void *unk15C;
    void *unk160;
    char pad164[0xCC];
    float unk230;
    float unk234;
    float unk238;
    char pad23C[0x8];
    float unk244;
    char pad248[0x8];
    union {
        float f;
        struct {
            long pad : 40;
            long clip : 3;
        } b;
    } unk250;
} ClipObj;

extern ClipObj *GetLayoutClass(void);
extern ClipCamera *iosgluGetCameraContext(void);
extern float modelClipSolid(ClipObj *, void *);
extern float modelClipSkin(ClipObj *, void *);

#ifdef NONMATCHING
/* 7 diffs: with -fno-strict-aliasing, the model pointer reload lands after the float-to-int conversion instead of before it */
void ClipLayoutObjModel(void) {
    ClipObj *lc;
    ClipObj *info;
    ClipVisual *v;
    ClipCamera *cam;
    float r;
    float scale;

    lc = GetLayoutClass();
    info = lc->unk140;
    info->unk30 = -1.0f;
    if (lc->unk144 != 0 && (info->unk34 = lc->unk144->unk244) < 1.0f) {
        v = lc->unk144->unk0->unk20;
        if (v->unk18 & 1) {
            lc->unk144->unk250.f = lc->unk9C;
            r = modelClipSkin(lc->unk144, lc->unk160);
        } else {
            if (v->unk8 != 0 && v->unk8->unk3C != 0 && (cam = iosgluGetCameraContext()) != 0) {
                scale = 1.0f / (cam->unkC / 500.0f);
            } else {
                scale = 1.0f;
            }
            lc->unk144->unk250.f = lc->unk9C * scale;
            r = modelClipSolid(lc->unk144, lc->unk15C);
        }
        lc->unk144->unk250.b.clip = (int)r;
        info->unk30 = (int)lc->unk144->unk250.b.clip;
        info->unk20 = lc->unk144->unk230;
        info->unk28 = lc->unk144->unk238;
        info->unk24 = lc->unk144->unk234;
    }
}
#endif
