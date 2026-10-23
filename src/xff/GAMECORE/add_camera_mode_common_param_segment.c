typedef struct Seg {
    int a;
    struct Seg *self;
} Seg;

typedef struct {
    char pad0[0x10];
    Seg seg0;
    char pad18[0x7C];
    Seg seg1;
    char pad9C[4];
    Seg seg2;
    char padA8[0xEC];
} CommonParam;

typedef struct {
    char pad0[0xC];
    int num;
    CommonParam *params;
} CommonParamManager;

void add_camera_mode_common_param_segment(CommonParamManager *m)
{
    CommonParam *p;
    int i;

    if (m != 0) {
        /* Dead store, but it makes gcc load params in the blez delay slot. */
        p = m->params;
        for (i = 0; i < m->num; i++) {
            p = &m->params[i];
            p->seg0.self = &p->seg0;
            p->seg1.self = &p->seg1;
            p->seg2.self = &p->seg2;
        }
    }
}
