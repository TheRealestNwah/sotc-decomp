typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; int i[4]; } Vec4;
extern void SetQuaternionByAxisRotateVWithNoRegularize(void *, short, Vec4 *);

void SetQuaternionByAxisRotate(void *q, short a, float x, float y, float z)
{
    Vec4 v, n;
    v.f[0] = x;
    v.f[1] = y;
    v.f[2] = z;
    v.i[3] = 0;
    __asm__ __volatile__("lqc2 vf05, 0(%1)\n"
                         "vmul.xyz vf07, vf05, vf05\n"
                         "vmulax.w ACC, vf00, vf07x\n"
                         "vmadday.w ACC, vf00, vf07y\n"
                         "vmaddz.w vf07, vf00, vf07z\n"
                         "vrsqrt Q, vf00w, vf07w\n"
                         "vwaitq\n"
                         "vmulq.xyz vf05, vf05, Q\n"
                         "sqc2 vf05, 0(%0)\n"
                         ".set noreorder\n.set reorder\n"
                         : : "r"(&n), "r"(&v) : "memory");
    SetQuaternionByAxisRotateVWithNoRegularize(q, a, &n);
}
