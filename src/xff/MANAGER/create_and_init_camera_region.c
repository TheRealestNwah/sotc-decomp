typedef struct {
    int unk0;
    int unk4;
    long unk8;
    int unk10;
    int unk14;
    int pad18[2];
    int unk20[4];
} CameraRegion;

extern void *iosMallocAlign(void *, int, int);
extern void func_000E86C8(CameraRegion *, int, int, long, int, int);

CameraRegion *create_and_init_camera_region(int unk0, int unk4, long unk8, int unk10, int unk14, void *heap)
{
    CameraRegion *region = iosMallocAlign(heap, sizeof(CameraRegion), 0x10);
    func_000E86C8(region, unk0, unk4, unk8, unk10, unk14);
    return region;
}
