typedef struct {
    int status;
    void *base;
    void *obj;
    void *region;
    int pad10[2];
    void *target;
} PlaceStatus;

extern void func_000D8E80(PlaceStatus *, void *, float);
extern void func_000D9028(PlaceStatus *, void *, float);
extern int is_parent_obj_boss_camera_region(void *);
extern void *GAMEUTIL_get_boss_obj(void);

void doit_camera_place_status(PlaceStatus *p, void *arg, float time)
{
    int status;
    void *base = 0;
    void *obj = 0;

    func_000D8E80(p, arg, time);
    func_000D9028(p, arg, time);
    if (p->target != 0) {
        status = 2;
        obj = p->target;
        base = obj;
    } else if (p->region != 0) {
        status = 1;
        base = *(void **)((char *)p->region + 0x10);
        if (is_parent_obj_boss_camera_region(p->region) == 1)
            obj = GAMEUTIL_get_boss_obj();
    } else {
        status = 0;
    }
    p->status = status;
    p->base = base;
    p->obj = obj;
}
