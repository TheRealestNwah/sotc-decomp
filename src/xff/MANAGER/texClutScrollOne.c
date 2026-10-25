typedef struct Rgba {
    unsigned char r, g, b, a;
} Rgba;

typedef struct Texture {
    char pad0[0x1C];
    int format;
} Texture;

typedef struct ClutScrollParam {
    unsigned int start;
    unsigned int end;
    int period;
    int step;
    int interpolate;
} ClutScrollParam;

/* Reached through a union: the accesses must alias the CLUT state stores. */
typedef struct ClutScroll {
    char pad0[0x40];
    union {
        ClutScrollParam clut;
        int raw[5];
    } u;
} ClutScroll;

typedef struct ClutState {
    char pad0[0x8];
    short offset;
    unsigned short timer;
    Rgba *clut;
    char pad10[0x30];
    Rgba *src;
    Rgba *work[2];
} ClutState;

extern const int RO_0013D5C0[];
extern const unsigned char RO_0013D6B0[];

int iosDlGetWorkBufId(void);
void *memcpy(void *, const void *, unsigned int);

int texClutScrollOne(void *unused, Texture *texture, ClutScroll *scroll, ClutState *state, int speed, int once)
{
    Rgba *dest;
    Rgba *src;
    int lo;
    int hi;
    int range;
    float t;
    int i;

    if (RO_0013D5C0[texture->format & 0x3F] == 0 || scroll->u.clut.step == 0 || speed == 0) {
        return 0;
    }
    dest = state->work[iosDlGetWorkBufId()];
    src = state->src;
    if (scroll->u.clut.start >= RO_0013D5C0[texture->format & 0x3F]) {
        scroll->u.clut.start = RO_0013D5C0[texture->format & 0x3F] - 1;
    }
    if (scroll->u.clut.end >= RO_0013D5C0[texture->format & 0x3F]) {
        scroll->u.clut.end = RO_0013D5C0[texture->format & 0x3F] - 1;
    }
    if (scroll->u.clut.end < scroll->u.clut.start) {
        lo = scroll->u.clut.end;
        hi = scroll->u.clut.start;
    } else {
        lo = scroll->u.clut.start;
        hi = scroll->u.clut.end;
    }
    range = hi - lo + 1;
    state->timer += speed;
    if (scroll->u.clut.period == 0 || scroll->u.clut.period < state->timer) {
        state->timer -= scroll->u.clut.period;
        t = 0.0f;
        state->offset += scroll->u.clut.step;
        if (once) {
            if (state->offset < 0 || state->offset >= range) {
                return 1;
            }
        }
    } else {
        t = (float)state->timer / (float)scroll->u.clut.period;
    }
    for (i = 0; i < RO_0013D5C0[texture->format & 0x3F]; i++) {
        if (lo <= i && i <= hi) {
            if (scroll->u.clut.interpolate) {
                int a = i + state->offset;
                int b = a + scroll->u.clut.step;
                Rgba *s0;
                Rgba *s1;
                Rgba *d;

                while (a < lo) {
                    a += range;
                }
                while (hi < a) {
                    a -= range;
                }
                while (b < lo) {
                    b += range;
                }
                while (hi < b) {
                    b -= range;
                }
                if ((texture->format & 0x3F) == 0x13 || (texture->format & 0x3F) == 0x1B) {
                    s0 = &src[RO_0013D6B0[a]];
                    s1 = &src[RO_0013D6B0[b]];
                    d = &dest[RO_0013D6B0[i]];
                } else {
                    s0 = &src[a];
                    s1 = &src[b];
                    d = &dest[i];
                }
                d->r = s0->r + (int)((s1->r - s0->r) * t);
                d->g = s0->g + (int)((s1->g - s0->g) * t);
                d->b = s0->b + (int)((s1->b - s0->b) * t);
                d->a = s0->a + (int)((s1->a - s0->a) * t);
            } else {
                int a = i + state->offset;
                Rgba *s0;
                Rgba *d;

                while (a < lo) {
                    a += range;
                }
                while (hi < a) {
                    a -= range;
                }
                if ((texture->format & 0x3F) == 0x13 || (texture->format & 0x3F) == 0x1B) {
                    d = &dest[RO_0013D6B0[i]];
                    s0 = &src[RO_0013D6B0[a]];
                } else {
                    d = &dest[i];
                    s0 = &src[a];
                }
                memcpy(d, s0, 4);
            }
        } else {
            *(int *)&dest[i] = *(int *)&src[i];
        }
    }
    while (state->offset < 0) {
        state->offset += range;
    }
    while (state->offset >= range) {
        state->offset -= range;
    }
    state->clut = dest;
    return 0;
}
