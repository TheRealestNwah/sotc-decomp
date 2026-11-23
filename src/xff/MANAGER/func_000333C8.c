typedef struct { unsigned char start, len; } Key8;
typedef struct { unsigned short start, len; } Key16;
typedef struct { unsigned int start, len; } Key32;

#define SCAN(T)                                                     \
    {                                                               \
        T *k = p;                                                   \
        int ret;                                                    \
        out[0] = out[1] = out[2] = 0;                               \
        ret = -1;                                                   \
        for (; k->len; k++) {                                       \
            int e = k->start + k->len;                              \
            float fe;                                               \
            if ((float)k->start < t && end <= (float)k->start)      \
                out[0] = 1;                                         \
            fe = e;                                                 \
            if (fe < t && end <= fe)                                \
                out[2] = 1;                                         \
            if (end <= (float)k->start && fe <= t) {                \
                out[1] = 1;                                         \
                ret = e;                                            \
            }                                                       \
            if ((float)k->start <= end && end <= fe) {              \
                out[1] = 1;                                         \
                ret = end;                                          \
            }                                                       \
            if ((float)k->start <= t && t <= fe) {                  \
                out[1] = 1;                                         \
                ret = t;                                            \
            }                                                       \
            if (t < (float)k->start)                                \
                break;                                              \
        }                                                           \
        return ret;                                                 \
    }

static int func_000333C8(unsigned char *out, int type, void **data, float t, float end)
{
    void *p = *data;
    if (!p)
        return -1;
    switch (type) {
    case 0:
        SCAN(Key8)
    case 1:
        SCAN(Key16)
    case 2:
        SCAN(Key32)
    }
    return -1;
}
