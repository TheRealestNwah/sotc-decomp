extern unsigned char gcGlobalVar[1];

typedef struct {
    float start;
    float target;
    float value;
    float speed;
} TimeFloat;

void Update_TimeFloatSpeed(TimeFloat *t)
{
    float target = t->target;
    float dir = 1.0f;

    if (target < t->start) {
        dir = -1.0f;
    }
    t->value += t->speed * dir * *(float *)(gcGlobalVar + 0x180);
    if (dir > 0.0f) {
        if (target < t->value) {
            t->value = target;
        }
    } else if (t->value < target) {
        t->value = target;
    }
}
