typedef struct {
    char pad0[0xA0];
    float s;
    float t;
    float r;
    int q;
} GlState;

extern GlState D_00130480;

void glTexCoord2fv(float *v)
{
    GlState *gl = &D_00130480;

    gl->s = v[0];
    gl->t = v[1];
    gl->r = 1.0f;
    /* Empty block found by the permuter: it splits the basic block, so the
       q store is scheduled after the others as in the original. */
    do {
    } while (0);
    gl->q = 0;
}
