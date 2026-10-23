typedef struct { char unknown00[4]; short frames; } MotionResource;

static inline void wrapFrame(float *frame, int limit)
{
    float end = (float)limit;
    if (limit == 0)
        *frame = 0.0f;
    else if (limit < 0)
        *frame = 0.0f;
    else {
        float current = *frame;
        if (end < current) {
            float next;
            do {
                next = current - end;
                current = next;
            } while (end < next);
            *frame = next;
        }
    }
}

static inline int reachedEnd(float end, float current)
{
    int reached = 1;
    if (!(end <= current))
        reached = 0;
    return reached;
}

int GetMotionFrameDirectResource(float *frame, float *total,
                                MotionResource *resource,
                                float step, float scale)
{
    float delta = scale * step;
    int limit = resource->frames - 1;
    int result = 0;
    *frame += delta;
    *total += delta;
    if (reachedEnd((float)limit, *frame)) {
        wrapFrame(frame, limit);
        result = 1;
    }
    return result;
}

int GetMotionFrameWithOutsideLimit(float *frame, float *total, int limit,
                                   float step, float scale)
{
    float delta = scale * step;
    int result = 0;
    *frame += delta;
    *total += delta;
    if (reachedEnd((float)limit, *frame)) {
        wrapFrame(frame, limit);
        result = 1;
    }
    return result;
}
