void iosMakeNormalLightMatrix(void *m, void *l0, void *l1, void *l2, void *l3)
{
    __asm__ __volatile__(".set noreorder
"
                         "vsubw.x vf5, vf0, vf0w
"
                         "lqc2 vf24, 0x0(%4)
"
                         "lqc2 vf25, 0x0(%0)
"
                         "lqc2 vf26, 0x0(%1)
"
                         "lqc2 vf27, 0x0(%2)
"
                         "vmulx.xyz vf24, vf24, vf5x
"
                         "vmulx.xyz vf25, vf25, vf5x
"
                         "vmulx.xyz vf26, vf26, vf5x
"
                         "vmulx.xyz vf27, vf27, vf5x
"
                         "vmul.xyz vf14, vf24, vf24
"
                         "vaddy.x vf14, vf14, vf14y
"
                         "vaddz.x vf14, vf14, vf14z
"
                         "vrsqrt Q, vf0w, vf14x
"
                         "vmul.xyz vf15, vf25, vf25
"
                         "vaddy.x vf15, vf15, vf15y
"
                         "vaddz.x vf15, vf15, vf15z
"
                         "vwaitq 
"
                         "vmulq.xyz vf24, vf24, Q
"
                         "vnop 
"
                         "vnop 
"
                         "vrsqrt Q, vf0w, vf15x
"
                         "vmul.xyz vf16, vf26, vf26
"
                         "vaddy.x vf16, vf16, vf16y
"
                         "vaddz.x vf16, vf16, vf16z
"
                         "vwaitq 
"
                         "vmulq.xyz vf25, vf25, Q
"
                         "vmul.xyz vf17, vf27, vf27
"
                         "vaddy.x vf17, vf17, vf17y
"
                         "vaddz.x vf17, vf17, vf17z
"
                         "vrsqrt Q, vf0w, vf16x
"
                         "vwaitq 
"
                         "vmulq.xyz vf26, vf26, Q
"
                         "vrsqrt Q, vf0w, vf17x
"
                         "vwaitq 
"
                         "vmulq.xyz vf27, vf27, Q
"
                         "vmove.xyzw vf14, vf24
"
                         "vmove.xyzw vf15, vf25
"
                         "vmove.xyzw vf16, vf26
"
                         "vmove.xyzw vf17, vf27
"
                         "vsub.xyzw vf5, vf0, vf0
"
                         "vaddx.y vf14, vf5, vf25x
"
                         "vaddx.z vf14, vf5, vf26x
"
                         "vaddx.w vf14, vf5, vf27x
"
                         "vaddy.x vf15, vf5, vf24y
"
                         "vaddy.z vf15, vf5, vf26y
"
                         "vaddy.w vf15, vf5, vf27y
"
                         "vaddz.x vf16, vf5, vf24z
"
                         "vaddz.y vf16, vf5, vf25z
"
                         "vaddz.w vf16, vf5, vf27z
"
                         "vaddw.x vf17, vf5, vf24w
"
                         "vaddw.y vf17, vf5, vf25w
"
                         "vaddw.z vf17, vf5, vf26w
"
                         "sqc2 vf14, 0x0(%3)
"
                         "sqc2 vf15, 0x10(%3)
"
                         "sqc2 vf16, 0x20(%3)
"
                         "sqc2 vf17, 0x30(%3)
"
                         ".set reorder
"
                         : : "r"(l1), "r"(l2), "r"(l3), "r"(m), "r"(l0) : "$6", "$7", "$8", "$9", "memory");
}
