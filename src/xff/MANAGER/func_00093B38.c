typedef struct Obj {
    int pad0[3];
    int type;
} Obj;

typedef struct Fade {
    Obj *obj;
    int pad4;
    unsigned int flags;
    float cur;
    float target;
    float speed;
    float timer;
    float v1C;
    float v20;
} Fade;

extern float rintf(float);

static void func_00093B38(Fade *s, float dt)
{
    float *p;
    float d;
    float step;
    float t;
    int r;

    s->timer -= dt;
    if (s->timer < 0.0f) {
        s->timer = 0.0f;
        r = 0;
    } else {
        r = 1;
    }
    if (r) {
        return;
    }
    switch (s->obj->type) {
    case 1:
        p = &s->v20;
        break;
    case 2:
        p = &s->v1C;
        break;
    case 3:
        p = &s->v1C;
        break;
    case 4:
        p = &s->v20;
        break;
    default:
        p = &s->cur;
        break;
    }
    d = s->target - *p;
    step = s->speed * dt;
    if (s->obj->type != 0) {
        s->cur = 1.0f;
        step = rintf(step);
        if (step < 0.0f ? step > -1.0f : step < 1.0f) {
            if (step > 0.0f) {
                step = 1.0f;
            }
            if (step < 0.0f) {
                step = -1.0f;
            }
        }
    }
    *p += step;
    t = s->target;
    if (d * (t - *p) <= 0.0f) {
        *p = t;
        if (t == 0.0f) {
            s->flags &= ~0xF;
        } else {
            s->flags = (s->flags & ~0xF) | 3;
        }
    }
}
