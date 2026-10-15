extern int camera_collision_check_direct(void *, void *, void *, void *, void *, int, void *, int);
extern void ConvertFromCollisionPointToDynamics(void *, void *);

int CAM_act_ray_check_for_camera(void *out, void *a, void *b, void *c, void *d, void *e)
{
    char buf[0x50] __attribute__((aligned(16)));
    int r = camera_collision_check_direct(buf, a, b, c, d, 0, e, 1) == 0;
    if (!r) {
        if (out != 0)
            ConvertFromCollisionPointToDynamics(out, buf);
    }
    return r;
}
