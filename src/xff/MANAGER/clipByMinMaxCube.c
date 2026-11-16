int clipByMinMaxCube(void *a, void *b, void *m)
{
    int r;
    int t;

    __asm__ __volatile__("lqc2 vf1, 0x0(%0)\n"
                         "lqc2 vf2, 0x0(%1)\n"
                         "lqc2 vf4, 0x0(%2)\n"
                         "lqc2 vf5, 0x10(%2)\n"
                         "lqc2 vf6, 0x20(%2)\n"
                         "vmove.w vf1, vf0\n"
                         "vmove.w vf2, vf0\n"
                         "lqc2 vf7, 0x30(%2)\n"
                         : : "r"(a), "r"(b), "r"(m) : "memory");
    r = 0x3F;
    __asm__ __volatile__("vmove.xyz vf10, vf1\n"
                         "vmove.x vf11, vf1\n"
                         "vmove.yz vf11, vf2\n"
                         "vmove.y vf15, vf2\n"
                         "vmove.x vf16, vf2\n"
                         "vmulax.xyzw ACC, vf4, vf10x\n"
                         "vmadday.xyzw ACC, vf5, vf10y\n"
                         "vmaddaz.xyzw ACC, vf6, vf10z\n"
                         "vmaddw.xyzw vf20, vf7, vf0w\n"
                         "vmove.y vf12, vf1\n"
                         "vmove.xz vf12, vf2\n"
                         "vmove.z vf13, vf1\n"
                         ".word 0x4BD4A1FF\n"
                         "vmulax.xyzw ACC, vf4, vf11x\n"
                         "vmadday.xyzw ACC, vf5, vf11y\n"
                         "vmaddaz.xyzw ACC, vf6, vf11z\n"
                         "vmaddw.xyzw vf21, vf7, vf0w\n"
                         "vmove.xy vf13, vf2\n"
                         "cfc2.ni %0, $vi18\n"
                         : "=r"(t) : : "memory");
    __asm__("and %0, %0, %1" : "+r"(r) : "r"(t));
    if (r != 0) {
        __asm__ __volatile__(".word 0x4BD5A9FF\n"
                             "vmulax.xyzw ACC, vf4, vf12x\n"
                             "vmadday.xyzw ACC, vf5, vf12y\n"
                             "vmaddaz.xyzw ACC, vf6, vf12z\n"
                             "vmaddw.xyzw vf20, vf7, vf0w\n"
                             "vmove.xy vf14, vf1\n"
                             "cfc2.ni %0, $vi18\n"
                             : "=r"(t) : : "memory");
        __asm__("and %0, %0, %1" : "+r"(r) : "r"(t));
        if (r != 0) {
            __asm__ __volatile__(".word 0x4BD4A1FF\n"
                                 "vmulax.xyzw ACC, vf4, vf13x\n"
                                 "vmadday.xyzw ACC, vf5, vf13y\n"
                                 "vmaddaz.xyzw ACC, vf6, vf13z\n"
                                 "vmaddw.xyzw vf21, vf7, vf0w\n"
                                 "vmove.z vf14, vf2\n"
                                 "cfc2.ni %0, $vi18\n"
                                 : "=r"(t) : : "memory");
            __asm__("and %0, %0, %1" : "+r"(r) : "r"(t));
            if (r != 0) {
                __asm__ __volatile__(".word 0x4BD5A9FF\n"
                                     "vmulax.xyzw ACC, vf4, vf14x\n"
                                     "vmadday.xyzw ACC, vf5, vf14y\n"
                                     "vmaddaz.xyzw ACC, vf6, vf14z\n"
                                     "vmaddw.xyzw vf20, vf7, vf0w\n"
                                     "vmove.xz vf15, vf1\n"
                                     "cfc2.ni %0, $vi18\n"
                                     : "=r"(t) : : "memory");
                __asm__("and %0, %0, %1" : "+r"(r) : "r"(t));
                if (r != 0) {
                    __asm__ __volatile__(".word 0x4BD4A1FF\n"
                                         "vmulax.xyzw ACC, vf4, vf15x\n"
                                         "vmadday.xyzw ACC, vf5, vf15y\n"
                                         "vmaddaz.xyzw ACC, vf6, vf15z\n"
                                         "vmaddw.xyzw vf21, vf7, vf0w\n"
                                         "vmove.yz vf16, vf1\n"
                                         "cfc2.ni %0, $vi18\n"
                                         : "=r"(t) : : "memory");
                    __asm__("and %0, %0, %1" : "+r"(r) : "r"(t));
                    if (r != 0) {
                        __asm__ __volatile__(".word 0x4BD5A9FF\n"
                                             "vmulax.xyzw ACC, vf4, vf16x\n"
                                             "vmadday.xyzw ACC, vf5, vf16y\n"
                                             "vmaddaz.xyzw ACC, vf6, vf16z\n"
                                             "vmaddw.xyzw vf20, vf7, vf0w\n"
                                             "vmove.xyz vf17, vf2\n"
                                             "cfc2.ni %0, $vi18\n"
                                             : "=r"(t) : : "memory");
                        __asm__("and %0, %0, %1" : "+r"(r) : "r"(t));
                        if (r != 0) {
                            __asm__ __volatile__(".word 0x4BD4A1FF\n"
                                                 "vmulax.xyzw ACC, vf4, vf17x\n"
                                                 "vmadday.xyzw ACC, vf5, vf17y\n"
                                                 "vmaddaz.xyzw ACC, vf6, vf17z\n"
                                                 "vmaddw.xyzw vf21, vf7, vf0w\n"
                                                 "vnop\n"
                                                 "cfc2.ni %0, $vi18\n"
                                                 : "=r"(t) : : "memory");
                            __asm__("and %0, %0, %1" : "+r"(r) : "r"(t));
                            if (r != 0) {
                                __asm__ __volatile__(".word 0x4BD5A9FF\n"
                                                     "vnop\n"
                                                     "vnop\n"
                                                     "vnop\n"
                                                     "vnop\n"
                                                     "vnop\n"
                                                     "cfc2.ni %0, $vi18\n"
                                                     : "=r"(t) : : "memory");
                                __asm__("and %0, %0, %1" : "+r"(r) : "r"(t));
                                if (r != 0) {
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return r;
}
