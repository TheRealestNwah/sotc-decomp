float iosRotTransCurrentMatrix(void *out, void *v)
{
    float r;
    __asm__ __volatile__("lqc2 vf08, 0x0(%2)\n"
                         "vmulax.xyzw ACC, vf01, vf08x\n"
                         "vmadday.xyzw ACC, vf02, vf08y\n"
                         "vmaddaz.xyzw ACC, vf03, vf08z\n"
                         "vmaddw.xyzw vf10, vf04, vf08w\n"
                         "vdiv Q, vf00w, vf10w\n"
                         "vwaitq\n"
                         "vmulq.xyz vf10, vf10, Q\n"
                         "vftoi4.xyz vf10, vf10\n"
                         "vsub.xy vf14, vf10, vf11\n"
                         "vsub.xy vf15, vf12, vf11\n"
                         "vsub.zw vf14, vf14, vf14\n"
                         "vsub.zw vf15, vf15, vf15\n"
                         "vopmula.xyz ACC, vf14, vf15\n"
                         "vopmsub.xyz vf16, vf15, vf14\n"
                         "vmr32.y vf16, vf16\n"
                         "vmr32.x vf16, vf16\n"
                         "sqc2 vf10, 0x0(%1)\n"
                         "qmfc2 $7, vf16\n"
                         "mtc1 $7, %0\n"
                         "vmove.xy vf12, vf11\n"
                         "vmove.xy vf11, vf10\n"
                         ".set noreorder\n.set reorder\n"
                         : "=f"(r) : "r"(out), "r"(v) : "$7", "memory");
    return r;
}
