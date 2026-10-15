typedef struct {
    int id;
    int a;
    long b;
    int c;
    int d;
    char pad18[8];
    float v[4];
} CameraRegion;

void constructor_camera_region(CameraRegion *r)
{
    r->id = -1;
    r->a = 0;
    r->b = 0;
    r->c = 0;
    r->d = 0;
    __asm__ __volatile__("sqc2 vf0, 0x0(%0)\n.set noreorder\n.set reorder\n" : : "r"(r->v) : "memory");
}
