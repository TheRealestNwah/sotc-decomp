typedef int s128 __attribute__((mode(TI)));

typedef struct {
    s128 q;
} Vec4;

extern Vec4 ZeroPoint;

typedef struct {
    int a;
    int b;
    int c;
    float d;
    Vec4 p0;
    Vec4 p1;
} VisibleAngleEntry;

typedef struct {
    int count;
    char pad4[0xC];
    VisibleAngleEntry entries[20];
    char pad_active[0x3E4 - 0x3D0];
    float limit;
} VisibleAngleManager;

extern void func_000DB6C0(VisibleAngleManager *, void *, void *);

void doit_camera_target_visible_angle_manager(VisibleAngleManager *mgr, void *b, void *c, void *d, float dt)
{
    VisibleAngleEntry *entry = mgr->entries;
    int i;
    int on = 1;

    for (i = 19; i >= 0; i--) {
        float lim = mgr->limit;

        if (entry->a == on) {
            entry->d += dt;
            if (lim <= entry->d) {
                entry->a = 0;
                entry->c = 0;
                entry->b = 0;
                entry->d = 0.0f;
                entry->p0 = ZeroPoint;
                entry->p1 = ZeroPoint;
            }
        }
        entry++;
    }
    func_000DB6C0(mgr, b, d);
}
