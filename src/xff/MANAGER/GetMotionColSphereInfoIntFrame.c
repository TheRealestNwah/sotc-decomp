#ifdef NONMATCHING /* 77 diffs: branch layout and short loads hoisted above the stores */
typedef struct {
    unsigned char id;
    unsigned char pad1;
    unsigned char type;
    unsigned char pad3;
    float *data;
    void *extra;
} Track;
typedef struct {
    short count;
    unsigned char pad2[0x2A];
    Track track;
} Motion;
extern void func_00032B78(float *, int, void *, int);

static inline void trackSphere(float *out, Track *t, int frame)
{
    float *d;
    float tmp[4];
    out[3] = 1.0f;
    {
        unsigned char type = t->type;
        d = t->data;
        if (type == 0) {
            out[0] = d[0];
            out[1] = d[1];
            out[2] = d[2];
        } else if (type != 2) {
            d += frame * 3;
            out[0] = d[0];
            out[1] = d[1];
            out[2] = d[2];
        } else {
            short *s = (short *)((int *)d)[6] + frame * 3;
            int i;
            for (i = 0; i < 3; i++)
                out[i] = s[i] * d[i * 2 + 1] * (1.0f / 32767.0f) + d[i * 2];
        }
    }
    func_00032B78(tmp, t->id, t->extra, frame);
    out[3] = tmp[1] * 0.5f;
}

int GetMotionColSphereInfoIntFrame(float *out, Motion *m, int frame)
{
    if (m->count >= 4 && m->track.data != 0) {
        trackSphere(out, &m->track, frame);
        return 1;
    }
    return 0;
}
#endif
