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

#ifdef NONMATCHING
/* 6 diffs: the invert flag load is scheduled first into a temp instead of last into the reused cond pointer register */
int func_0004E5F8(CondState *s, Cond *c)
{
    int type = c->type;
    unsigned long mask = c->mask;
    int r = 0;
    long match = c->match;
    RangeVal *sub = &s->sub;
    float max = c->max;
    float min = c->min;
    int lo, hi;
    int inv;

    inv = c->invert;

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
#endif
