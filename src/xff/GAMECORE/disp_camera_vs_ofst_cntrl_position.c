typedef struct {
    float x, y, z, w;
} __attribute__((aligned(8))) Vec4;
typedef struct {
    char pad[0xC];
    int n;
    float (*pts)[3];
} Seg;

extern Seg *B_0019FCF8[];
extern void glDrawNull(Vec4 *, float *, int, float);

void disp_camera_vs_ofst_cntrl_position(int mtx, float alpha)
{
    float color[4];
    Vec4 pos;
    Vec4 t;
    Seg *s;
    float (*p)[3];
    int i;
    int j;

    color[0] = 1.0f;
    color[1] = 0.5f;
    color[2] = 0.5f;
    color[3] = alpha;
    for (i = 0; i < 10; i++) {
        s = B_0019FCF8[i];
        if (s == 0)
            continue;
        p = s->pts;
        for (j = 0; j < s->n; j++) {
            t.x = p[j][0];
            t.y = p[j][1];
            t.z = p[j][2];
            t.w = 1.0f;
            pos = t;
            glDrawNull(&pos, color, mtx, 2.0f);
        }
    }
}
