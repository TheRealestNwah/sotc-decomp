extern char *GetLayoutClass(void *);
extern void StabilizeToYRotQuaternion(void *);
extern void norootdynamics(void *, void *, float, void *, float, float, void *, float, void *);

void norootdynamics_vel_xzstab(void *obj, void *a1, void *a2, void *a3, void *a4, float f0, float dt,
                               float f2, float f3)
{
    float vel[4] __attribute__((aligned(16)));
    char *cls = GetLayoutClass(obj);
    float *src;
    unsigned int bits;

    StabilizeToYRotQuaternion(*(void **)(cls + 0x13C));
    src = (float *)(cls + 0x30);

    __asm__ __volatile__(".set noreorder\n"
                         "mfc1 %0, %3\n"
                         "lqc2 vf5, 0(%2)\n"
                         "qmtc2.ni %0, vf6\n"
                         "vmulx.xyz vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0(%1)\n"
                         ".set reorder\n"
                         : "=r"(bits) : "r"(vel), "r"(src), "f"(dt) : "memory");
    /* Permuter-found: keeps cls live in its own register. */
    cls++;
    cls--;
    __asm__ __volatile__(".set noreorder\n"
                         "lqc2 vf5, 0(%1)\n"
                         "lqc2 vf6, 0(%2)\n"
                         "vadd.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0(%0)\n"
                         ".set reorder\n"
                         : : "r"(*(void **)(cls + 0x134)), "r"(*(void **)(cls + 0x138)), "r"(vel) : "memory");
    norootdynamics(obj, a1, f0, a2, dt, f2, a3, f3, a4);
}
