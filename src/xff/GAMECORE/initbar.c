typedef int ti __attribute__((mode(TI)));
typedef union { ti q; float v[4]; } s128;

typedef struct {
    float color[4];
    s128 pos;
    s128 size;
    float w;
    float h;
    float value;
    union { int i; float f; } id;
    float target;
    float disp;
    float max;
    int count;
    int pad50;
    float scale;
} Bar;

void initbar(Bar *bar, int id, float *color, s128 *pos, s128 *size, float value, float w, float h)
{
    bar->color[0] = color[0];
    bar->color[1] = color[1];
    bar->color[2] = color[2];
    bar->color[3] = color[3];
    bar->id.i = id;
    bar->pos.q = pos->q;
    bar->size.q = size->q;

    bar->w = w;
    bar->h = h;
    bar->max = bar->disp = bar->target = bar->value = value;
    bar->scale = 1.0f;
    bar->count = 0;
}
