/* Transform a point and form the near/far depth pair in VU0. */
void getZ(float *out, const float *point, const float *matrix)
{
    __asm__ __volatile__(
        "lqc2 vf01, 0(%1)\n"
        "lqc2 vf24, 0(%2)\n"
        "lqc2 vf25, 16(%2)\n"
        "lqc2 vf26, 32(%2)\n"
        "lqc2 vf27, 48(%2)\n"
        "vmulax.xyzw ACC, vf24, vf01x\n"
        "vmadday.xyzw ACC, vf25, vf01y\n"
        "vmaddaz.xyzw ACC, vf26, vf01z\n"
        "vmaddw.xyzw vf28, vf27, vf00w\n"
        "vmr32.y vf28, vf28\n"
        "vmr32.x vf28, vf28\n"
        "vaddw.x vf28, vf28, vf01w\n"
        "vsubw.z vf28, vf28, vf01w\n"
        "vnop\n" "vnop\n" "vnop\n"
        "sqc2 vf28, 0(%0)\n"
        ".set noreorder\n.set reorder\n"
        : : "r"(out), "r"(point), "r"(matrix) : "memory");
}
