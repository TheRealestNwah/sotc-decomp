typedef struct { float f[4]; } Q;

static inline void norm(Q *d, Q *s)
{
    __asm__ __volatile__("lqc2 vf14, 0(%1)\nvmul.xyzw vf15, vf14, vf14\nvaddy.x vf15, vf15, vf15y\nvaddz.x vf15, vf15, vf15z\nvaddw.x vf15, vf15, vf15w\nvrsqrt Q, vf00w, vf15x\nvwaitq\nvmulq.xyzw vf15, vf14, Q\nsqc2 vf15, 0(%0)\n" : : "r"(d), "r"(s) : "memory");
}

void CopyMultiQuaternionFromMotionRotElem(Q *dst, Q *src, int n)
{
    int i;
    for (i = 0; i < n; i++)
        norm(&dst[i], &src[i]);
}
