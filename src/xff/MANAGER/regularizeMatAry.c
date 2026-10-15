typedef struct { float f[4]; } Q;

void regularizeMatAry(Q *m, int n)
{
    while (n-- != 0) {
        __asm__ __volatile__("lqc2 vf14, 0(%1)\nvmul.xyzw vf15, vf14, vf14\nvaddy.x vf15, vf15, vf15y\nvaddz.x vf15, vf15, vf15z\nvaddw.x vf15, vf15, vf15w\nvrsqrt Q, vf00w, vf15x\nvwaitq\nvmulq.xyzw vf15, vf14, Q\nsqc2 vf15, 0(%0)\n" : : "r"(m), "r"(m) : "memory");
        m++;
    }
}
