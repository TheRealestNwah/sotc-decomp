typedef struct {
    char pad0[0x7C];
    int cols;
    int rows;
    char pad84[0x120 - 0x84];
    int count;
    float frames;
    float cols_f;
    float u_step;
    float v_step;
} TexAnim;

void init_texture_animation_parameter(TexAnim *t)
{
    int cols = t->cols;
    int rows = t->rows;

    t->count = cols * rows;
    if (t->count < 2) {
        t->frames = 1.0f; t->cols_f = 1.0f; t->u_step = 1.0f; t->v_step = 1.0f;
        return;
    }
    t->cols_f = cols;
    t->frames = t->count;
    t->u_step = 1.0f / (float)cols;
    t->v_step = 1.0f / (float)rows;
}
