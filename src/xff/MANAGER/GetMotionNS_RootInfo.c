typedef struct { int pad[2]; void *data; } MotionNode;
typedef struct { int pad; short num; short pad6; int pad8[2]; MotionNode *nodes; } Motion;
extern void func_0003A168(void *, void *);
extern void func_0003A4A8(float *, void *, void *, float, float, int);

void GetMotionNS_RootInfo(void *a, float *out, Motion *m, int idx, float t0, float t1, float scale)
{
    MotionNode *node = &m->nodes[idx];
    int n = m->num;

    /* The do/while(0) block gives d its own scope, which puts it in s1 ahead of a. */
    do {
        void *d = node->data;

        func_0003A168(a, d);
        func_0003A4A8(out, a, d, t0, t1, n);
        __asm__ __volatile__(
            "lqc2 vf5, 0x0(%0)\n"
            "qmtc2.ni %1, vf6\n"
            "vmulx.xyz vf5, vf5, vf6x\n"
            "sqc2 vf5, 0x0(%0)\n"
            : : "r"(out), "r"(scale) : "memory");
        out[3] = 0.0f;
    } while (0);
}
