typedef struct {
    unsigned char type;
    char pad1[0xB];
    void *keys;
} OptEntry;
typedef struct {
    char pad0[0x18];
    int count;
    OptEntry *entries;
    char pad20[8];
    unsigned char *ids;
} MotionRes;
typedef struct { unsigned char start, len; } Key8;
typedef struct { unsigned short start, len; } Key16;
typedef struct { unsigned int start, len; } Key32;

static inline int findOptionNode(MotionRes *r, int id)
{
    int i;
    int n = r->count;
    unsigned char *p = r->ids;
    for (i = 0; i < n; i++, p++) {
        if (*p == id)
            return i;
    }
    return -1;
}

float GetMotionOptionNodeNextSwitchFrameDirectResource(void *a, MotionRes *r, int id, float frame, int start)
{
    float result = -1.0f;
    int i = findOptionNode(r, id);
    OptEntry *e;
    void **p;

    if (i >= 0) {
    e = &r->entries[i];
    p = &e->keys;
    if (p != 0)
    switch (e->type) {
    case 0: {
        Key8 *k = *p, *q;
        int found = 0;
        for (q = k; q->len != 0; q++) {
            float v = start ? q->start : q->start + q->len;
            if (frame < v) {
                result = v;
                found = 1;
                break;
            }
        }
        if (!found)
            result = start ? k->start : k->start + k->len;
        break;
    }
    case 1: {
        Key16 *k = *p, *q;
        int found = 0;
        for (q = k; q->len != 0; q++) {
            float v = start ? q->start : q->start + q->len;
            if (frame < v) {
                result = v;
                found = 1;
                break;
            }
        }
        if (!found)
            result = start ? k->start : k->start + k->len;
        break;
    }
    case 2: {
        Key32 *k = *p, *q;
        int found = 0;
        for (q = k; q->len != 0; q++) {
            if (start) {
                if (frame < (float)q->start) {
                    result = q->start;
                    found = 1;
                    break;
                }
            } else {
                float v = (int)(q->start + q->len);
                if (frame < v) {
                    result = v;
                    found = 1;
                    break;
                }
            }
        }
        if (!found)
            result = start ? k->start : k->start + k->len;
        break;
    }
    }
    }
    return result;
}
