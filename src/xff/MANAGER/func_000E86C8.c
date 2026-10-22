typedef struct {
    int unk0;
    int unk4;
    long unk8;
    int unk10;
    int unk14;
    int pad18[2];
    int unk20[4];
} CameraRegion;

static void func_000E86C8(CameraRegion *r, int unk0, int unk4, long unk8, int unk10, int unk14)
{
    r->unk0 = unk0;
    r->unk4 = unk4;
    r->unk8 = unk8;
    r->unk10 = unk10;
    r->unk14 = unk14;
}
