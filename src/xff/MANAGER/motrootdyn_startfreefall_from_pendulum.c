extern float ZeroPoint[];
extern void charrootdyn_updateCharacterClassParentGeometry(char *, float *, float *);
extern void func_0005CD18(void *, char *);

void motrootdyn_startfreefall_from_pendulum(void *motion, char *chara)
{
    float offset[4] __attribute__((aligned(16)));
    float *dst = offset;
    float *q = (float *)(chara + 0x5A0);
    __asm__ __volatile__("lqc2 vf08, 0x0(%0)\n" : : "r"(chara + 0xC10));
    __asm__ __volatile__("vaddw.xyz vf12, vf00, vf00w\n"
                         "lqc2 vf11, 0x0(%1)\n"
                         "vmr32.w vf14, vf00\n"
                         "vmr32.w vf15, vf00\n"
                         "vmr32.w vf16, vf00\n"
                         "vopmula.xyz ACC, vf11, vf12\n"
                         "vmadd.xyz vf11, vf00, vf00\n"
                         "vmadd.xyz vf10, vf11, vf12\n"
                         "vmul.xyz vf13, vf11, vf10\n"
                         "vopmula.xyz ACC, vf11, vf10\n"
                         "vmaddw.xyz vf15, vf10, vf11w\n"
                         "vmsubw.xyz vf16, vf10, vf11w\n"
                         "vopmula.xyz ACC, vf13, vf12\n"
                         "vmadd.xyz vf17, vf13, vf12\n"
                         "vopmula.xyz ACC, vf15, vf12\n"
                         "vmadd.xyz vf15, vf00, vf00\n"
                         "vsub.xyz vf14, vf12, vf17\n"
                         "vmove.yz vf17, vf14\n"
                         "vmove.y vf14, vf16\n"
                         "vmove.y vf16, vf15\n"
                         "vmove.y vf15, vf17\n"
                         "vmove.z vf14, vf15\n"
                         "vmove.z vf15, vf16\n"
                         "vmove.z vf16, vf17\n"
                         "vmulax.xyzw ACC, vf14, vf08x
"
                         "vmadday.xyzw ACC, vf15, vf08y
"
                         "vmaddaz.xyzw ACC, vf16, vf08z
"
                         "vmaddw.xyzw vf10, vf00, vf08w
"
                         "sqc2 vf10, 0x0(%0)
"
                         : : "r"(dst), "r"(q) : "memory");
    charrootdyn_updateCharacterClassParentGeometry(chara, ZeroPoint, offset);
    func_0005CD18(motion, chara);
}
