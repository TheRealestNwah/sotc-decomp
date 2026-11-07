typedef struct {
    int enable;
    float value;
} RangeVal;

typedef struct {
    int enable;
    float value;
    unsigned long flags;
    RangeVal sub;
} CondState;

typedef struct {
    int type;
    float min;
    int pad8;
    float max;
    int pad10[2];
    unsigned long mask;
    long match;
    int invert;
} Cond;

static int func_0004E5F8(CondState *s, Cond *c)
{
    int type = c->type;
    int r = 0;
    RangeVal *sub = &s->sub;
    long match = c->match;
    float max = c->max;
    float min = c->min;
    int inv = c->invert;
    unsigned long mask = c->mask;
    int lo, hi;

    switch (type) {
    case 4:
        if (s->enable != 0) {
            unsigned long m = s->flags & mask;
            if (match < 0) {
                if (m != 0) {
                    r = 1;
                }
            } else if (m == match) {
                r = 1;
            }
        }
        break;
    case 2:
        if (s->enable != 0) {
            lo = 1;
            if (!(min < -180.0f) && !(min <= s->value)) {
                lo = 0;
            }
            hi = 1;
            if (!(max < -180.0f) && !(s->value <= max)) {
                hi = 0;
            }
            r = lo && hi;
        }
        break;
    case 0x51:
        if (sub->enable != 0) {
            lo = 1;
            if (!(min < -10000.0f) && !(min <= sub->value)) {
                lo = 0;
            }
            hi = 1;
            if (!(max < -10000.0f) && !(sub->value <= max)) {
                hi = 0;
            }
            r = lo ? hi : 0;
        }
        break;
    }
    return inv ? r : !r;
}
