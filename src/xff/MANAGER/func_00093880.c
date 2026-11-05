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

#ifdef NONMATCHING
/* 16 diffs: float register allocation in the rate tail */
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
        rate = (f->pos - *startOf(f, dir)) * 5.0f;
    else
        rate = (f->pos - *startOf(f, dir)) / parent->pos;
    f->rate = rate;
    f->time = parent->rate;
}
#endif
