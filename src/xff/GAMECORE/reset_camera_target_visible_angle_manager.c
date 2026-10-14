typedef int s128 __attribute__((mode(TI)));

typedef struct {
    s128 q;
} Vec4;

extern Vec4 ZeroPoint;

typedef struct {
    int a;
    int b;
    int c;
    int d;
    Vec4 p0;
    Vec4 p1;
} VisibleAngleEntry;

typedef struct {
    int count;
    char pad4[0xC];
    VisibleAngleEntry entries[20];
    int active;
    float angle0;
    float angle1;
} VisibleAngleManager;

void reset_camera_target_visible_angle_manager(VisibleAngleManager *mgr)
{
    VisibleAngleEntry *entry;
    int i;

    mgr->count = 0;
    entry = mgr->entries;
    for (i = 19; i >= 0; i--) {
        entry->a = 0;
        entry->c = 0;
        entry->b = 0;
        entry->d = 0;
        entry->p0 = ZeroPoint;
        entry->p1 = ZeroPoint;
        entry++;
    }
    mgr->active = 0;
    mgr->angle0 = mgr->angle1 = 0.0f;
}
