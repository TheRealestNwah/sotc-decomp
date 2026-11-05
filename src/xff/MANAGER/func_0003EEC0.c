typedef int s128 __attribute__((mode(TI)));
typedef struct { char pad0[4]; float max; float min; char padC[0xC]; } Limit;
typedef struct { char pad0[8]; int mode; char padC[0x44]; float rot[4] __attribute__((aligned(16))); } Obj;

static void func_0003EEC0(Obj *obj, float *in, s128 *src, Limit *lim)
{
    volatile s128 old;
    int i;

    if (obj->mode == 1) {
        *(s128 *)obj->rot = *src;
        return;
    }
    old = *(s128 *)obj->rot;
    for (i = 0; i < 3; i++) {
        float v = in[i];
        float max = lim[i].max * 0.0174532935f;
        float min = lim[i].min * 0.0174532935f;
        if (v >= 0.0f) {
            if (max < v)
                v = max;
        } else if (v < min) {
            v = min;
        }
        obj->rot[i] = v;
    }
}
