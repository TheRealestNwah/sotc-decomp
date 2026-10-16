typedef struct Seg {
    int a;
    struct Seg *self;
} Seg;

typedef struct {
    char pad0[0x10];
    Seg seg[7];
} SegGroup;

typedef struct {
    char pad0[0xC];
    int num;
    SegGroup *groups;
} SegManager;

void add_camera_mode_manager_segment(SegManager *m)
{
    SegGroup *g;
    int i;

    if (m != 0) {
        /* Dead store, but it makes gcc load groups in the blez delay slot. */
        g = m->groups;
        for (i = 0; i < m->num; i++) {
            g = &m->groups[i];
            g->seg[0].self = &g->seg[0];
            g->seg[1].self = &g->seg[1];
            g->seg[2].self = &g->seg[2];
            g->seg[3].self = &g->seg[3];
            g->seg[4].self = &g->seg[4];
            g->seg[5].self = &g->seg[5];
            g->seg[6].self = &g->seg[6];
        }
    }
}
