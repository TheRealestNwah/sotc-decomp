typedef int s128 __attribute__((mode(TI)));

typedef struct {
    float pad0;
    float min;
    float max;
    float start;
    float v[5];
    float range;
} NeckLimit;

typedef struct {
    int moving;
    char pad04[0xC];
    float speed[4];
    union {
        s128 q;
        float f[4];
    } cur;
} NeckState;

extern s128 ZeroVector;
extern void *memset(void *, int, unsigned int);
extern float func_0003F3F8(NeckLimit *l, float x, float y, float z);

#ifdef NONMATCHING
/* 40 diffs: register allocation in the diff loop and branch layout of the done test */
static void func_0003EF60(s128 *out, NeckState *st, float *in, NeckLimit *lim, float dt)
{
    float goal[4];
    float diff[3];
    float *o;
    int i;
    int done;

    memset(goal, 0, 0x10);
    memset(diff, 0, 0xC);
    *out = st->cur.q;
    for (i = 0; i < 3; i++) {
        float range = lim[i].range * 0.0174532925f;
        float min = lim[i].min * 0.0174532925f;
        float max = lim[i].max * 0.0174532925f;
        float x = in[i];

        if (3.14159265358979f - range < x || x < range + -3.14159265358979f) {
            if (0.0f < st->cur.f[i])
                goal[i] = max;
            else
                goal[i] = min;
        } else if (max < x) {
            goal[i] = max;
        } else if (x < min) {
            goal[i] = min;
        } else {
            goal[i] = x;
        }
    }
    for (i = 0; i < 3; i++) {
        float d = goal[i] - st->cur.f[i];
        if (d < 0.0f)
            d = -d;
        diff[i] = d;
    }
    if (st->moving == 0) {
        for (i = 0; i < 3; i++) {
            if (lim[i].start * 0.0174532925f <= diff[i]) {
                *(s128 *)st->speed = ZeroVector;
                st->moving = 1;
                break;
            }
        }
    }
    if (st->moving == 1) {
        o = (float *)out;
        done = 1;
        for (i = 0; i < 3; i++) {
            st->speed[i] = func_0003F3F8(&lim[i], st->speed[i], diff[i], dt);
            if (st->cur.f[i] < goal[i]) {
                o[i] += st->speed[i] * dt;
                if (goal[i] < o[i])
                    o[i] = goal[i];
            } else if (goal[i] < st->cur.f[i]) {
                o[i] -= st->speed[i] * dt;
                if (o[i] < goal[i])
                    o[i] = goal[i];
            } else {
                o[i] = goal[i];
            }
            if (o[i] != goal[i])
                done = 0;
        }
        if (done)
            st->moving = 0;
    }
}
#endif
