typedef int s128 __attribute__((mode(TI)));
extern int camera_collision_check_direct(void *out, s128 *from, s128 *to, void *x, int a, int b, void *e, int c);

static int func_000ED530(void *out, s128 *from, s128 *to, void *x, void *e)
{
    s128 hit[5];
    s128 pos;

    if (camera_collision_check_direct(hit, from, to, x, 1, 1, e, 0) == 1) {
        pos = hit[4];
    } else {
        pos = *to;
    }
    return camera_collision_check_direct(out, &pos, from, x, 1, 1, e, 0);
}
