extern float iosGetTableSin(int);
extern float iosGetTableCos(int);

static inline void scaleVec(float *dst, float *src, float s)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "qmtc2 %2, vf6\n"
                         "vmulx.xyzw vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(dst), "r"(src), "r"(s) : "memory");
}

void SetQuaternionByAxisRotateWithNoRegularize(float *q, int a, float x, float y, float z)
{
    float v[4] __attribute__((aligned(16)));
    float *p = v;
    int h = (short)a >> 1;
    v[0] = x;
    v[1] = y;
    v[2] = z;
    ((int *)v)[3] = 0;
    scaleVec(q, p, iosGetTableSin(h));
    q[3] = iosGetTableCos(h);
}
