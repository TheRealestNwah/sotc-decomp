extern void FilterCopyCollisionDynamics(void *, void *);
extern void CopyCollisionDynamics(void *, void *);
extern void GetCollisionDBCurrentPointOnLastPlane(void *, void *, void *);
extern int GAMEUTIL_is_nearly_equal_zero3D(void *, float);

void GAMEUTIL_set_data_by_dynamics_collision_info(char *o, void *src, int filter)
{
    if (filter == 1)
        FilterCopyCollisionDynamics(o + 0x10, src);
    else
        CopyCollisionDynamics(o + 0x10, src);
    GetCollisionDBCurrentPointOnLastPlane(o + 0x40, o + 0x30, o + 0x10);
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(o + 0x50), "r"(o + 0x10), "r"(o + 0x40) : "memory");
    if (GAMEUTIL_is_nearly_equal_zero3D(o + 0x50, 0.001f) == 1)
        *(int *)o = 1;
    else
        *(int *)o = 2;
}
