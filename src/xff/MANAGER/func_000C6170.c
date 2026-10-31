typedef int s128 __attribute__((mode(TI)));

typedef struct {
    char pad[0x40];
    s128 pos;
} Hit;

extern float *D_001370D8;
extern s128 *GetGeometryPointerSurfacePlane(void *);
extern int radiate_particle_collision_check_ray(Hit *, s128 *, char *, float);
extern void func_000C6288(char *, char *);

static void func_000C6170(char *o, char *p)
{
    int mode = *(int *)(p + 0x104);

    if (mode == 1) {
        func_000C6288(o, p);
    } else if (mode == 2) {
        float t = *(float *)(o + 0x184);
        float r = *(float *)(p + 0x110) / 30.0f;
        float a = *(float *)(p + 0x108);

        if (t <= 0.0f) {
            struct {
                s128 dir;
                Hit hit;
            } s;
            int res = radiate_particle_collision_check_ray(&s.hit, &s.dir, o, a);

            *(int *)(o + 0x188) = res;
            if (res == 1) {
                *(s128 *)(o + 0xA0) = s.hit.pos;
                *(s128 *)(o + 0xB0) = *GetGeometryPointerSurfacePlane(&s.hit);
            }
            *(float *)(o + 0x184) = r;
        } else {
            *(float *)(o + 0x184) = t - *D_001370D8;
        }
    }
}
