typedef struct Fade {
    struct Fade *parent;
    int pad4;
    int flags;
    float start0;
    float pos;
    float rate;
    float time;
    float start1;
    float start2;
} Fade;

extern int getDrawScreenWidth(void);
extern int getDrawScreenHeight(void);

static inline float *startOf(Fade *f, int dir)
{
    switch (dir) {
    case 1:
        return &f->start2;
    case 2:
        return &f->start1;
    case 3:
        return &f->start1;
    case 4:
        return &f->start2;
    default:
        return &f->start0;
    }
}


/* Defined before func_00098948: as an extern prototype gcc fills its first case branch as beql. */
static void func_00093880(Fade *f, unsigned int dir)
{
    Fade *parent;
    int kind;
    float rate;
    kind = f->flags & 0xF;

    if (kind == 1) {
        switch (dir) {
        case 0:
            f->pos = 1.0f;
            break;
        case 1:
            f->pos = 0.0f;
            break;
        case 2:
            f->pos = 0.0f;
            break;
        case 3:
            f->pos = 0.0f;
            break;
        case 4:
            f->pos = 0.0f;
            break;
        }
    } else if (kind == 4) {
        switch (dir) {
        case 0:
            f->pos = 0.0f;
            break;
        case 1:
            f->pos = -getDrawScreenHeight();
            break;
        case 2:
            f->pos = -getDrawScreenWidth();
            break;
        case 3:
            f->pos = getDrawScreenWidth();
            break;
        case 4:
            f->pos = getDrawScreenHeight();
            break;
        }
    }
    parent = f->parent;
    if (parent->pos <= 0.0f)
    parent = f->parent;
    if (parent->pos <= 0.0f) {
        f->rate = (f->pos - *startOf(f, dir)) * 5.0f;
    } else {
        f->rate = (f->pos - *startOf(f, dir)) / f->parent->pos;
    }
    f->time = parent->rate;
}

typedef struct { int *p; int pad; unsigned int state : 4; } Obj;

static void func_00098948(Obj *o)
{
    switch (o->state) {
    case 1:
        func_00093880((Fade *)o, o->p[3]);
        o->state = 2;
        break;
    case 4:
        func_00093880((Fade *)o, o->p[3]);
        o->state = 5;
        break;
    }
}
