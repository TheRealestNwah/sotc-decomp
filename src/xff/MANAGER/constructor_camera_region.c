typedef struct {
    int unk0;
    int unk4;
    long unk8;
    int unk10;
    int unk14;
    int pad18[2];
    int unk20[4];
} CameraRegion;

void constructor_camera_region(CameraRegion *r)
{
    r->unk0 = -1;
    r->unk4 = 0;
    r->unk8 = 0;
    r->unk10 = 0;
    r->unk14 = 0;
    __asm__ __volatile__(".set noreorder\n"
                         "sqc2 vf0, 0x0(%0)\n"
                         ".set reorder\n"
                         : : "r"(r->unk20) : "memory");
}
