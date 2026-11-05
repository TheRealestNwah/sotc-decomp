typedef struct { int pad0; float yaw; float pitch; } AngleEnt;
typedef struct { char pad[0x3D0]; int valid; float yaw; float pitch; } AngleMgr;
typedef struct { char pad[0xA94]; float yaw; } CamWork;

extern int GAMEUTIL_is_between_yaw_and_yaw(float, float, float);
extern float GAMEUTIL_get_difference_yaw_and_yaw(float, float);
static void func_000DBC18(int *, AngleEnt **);
static int func_000DBC88(int, AngleEnt **, AngleMgr *, CamWork *);
static int func_000DBD88(AngleEnt *, AngleMgr *, CamWork *, float, float);

int begin_and_update_get_yaw_pitch_camera_target_visible_angle_manager(float *yaw, float *pitch, AngleMgr *mgr, CamWork *cam, float y0, float p0)
{
    AngleEnt *list[20];
    int n;
    int idx, prev, next;
    AngleEnt **pc, **pp, **pn, **pe;
    float tyaw;
    float d;
    AngleEnt *e;

    n = 0;
    tyaw = cam->yaw;
    *yaw = y0;
    *pitch = p0;
    func_000DBC18(&n, list);
    idx = func_000DBC88(n, list, mgr, cam);
    if (idx < 0) {
        return 0;
    }
    if (n != 1) {
        prev = idx - 1;
        next = idx + 1;
        if (next >= n) next = 0;
        if (prev < 0) prev = n - 1;
        if (prev == next) {
            if (GAMEUTIL_is_between_yaw_and_yaw(tyaw, list[idx]->yaw, list[next]->yaw) != 1) {
                idx = next;
            }
        } else {
            pc = &list[idx];
            idx = next;
            pp = &list[prev];
            if (GAMEUTIL_is_between_yaw_and_yaw(tyaw, (*pc)->yaw, (*pp)->yaw) != 1) {
                pn = &list[next];
                idx = prev;
                if (GAMEUTIL_is_between_yaw_and_yaw(tyaw, (*pc)->yaw, (*pn)->yaw) != 1) {
                    d = GAMEUTIL_get_difference_yaw_and_yaw((*pp)->yaw, (*pc)->yaw);
                    if (!(d < GAMEUTIL_get_difference_yaw_and_yaw((*pn)->yaw, (*pc)->yaw))) {
                        idx = next;
                    }
                }
            }
        }
    }
    pe = &list[idx];
    if (func_000DBD88(*pe, mgr, cam, y0, p0) == 1) {
        *yaw = mgr->yaw;
    } else {
        e = *pe;
        mgr->yaw = e->yaw;
        mgr->pitch = e->pitch;
        *yaw = e->yaw;
        mgr->valid = 1;
    }
    return 1;
}
