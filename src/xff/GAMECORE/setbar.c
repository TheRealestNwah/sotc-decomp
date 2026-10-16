typedef struct {
    char pad[0x30];
    float k30;
    float k34;
    float k38;
    float pad3C;
    float max;
    float prev;
    float cur;
    float r4C;
    float r50;
    float r54;
} Bar;

void setbar(Bar *b, float v)
{
    if (b->cur == v)
        return;
    b->cur = v;
    b->prev = b->max;
    if (v < b->max) {
        if (0.0f < v)
            b->r4C = (b->max - v) / b->k38 * b->k30;
        b->r54 = (b->prev - b->cur) / b->k38 * b->k34 + 1.0f;
    }
    b->r50 = (b->prev - b->cur) * 0.03f;
}
