void GetMultiLocalizeMatrix(char *dst, char *src, int n)
{
    while (n-- != 0) {
        __asm__ __volatile__("lqc2 vf24, 0x30(%1)\n"
                             "vsubw.x vf25, vf00, vf00w\n"
                             "vmulx.xyz vf28, vf24, vf25x\n"
                             "vsub.w vf28, vf28, vf28\n"
                             "lq $8, 0x0(%1)\n"
                             "lq $9, 0x10(%1)\n"
                             "lq $10, 0x20(%1)\n"
                             "qmfc2 $11, vf00\n"
                             "pextlw $12, $9, $8\n"
                             "pextuw $13, $9, $8\n"
                             "pextlw $14, $11, $10\n"
                             "pextuw $15, $11, $10\n"
                             "pcpyld $8, $14, $12\n"
                             "pcpyud $9, $12, $14\n"
                             "pcpyld $10, $15, $13\n"
                             "pcpyud $11, $13, $15\n"
                             "qmtc2 $8, vf24\n"
                             "qmtc2 $9, vf25\n"
                             "qmtc2 $10, vf26\n"
                             "vmulax.xyzw ACC, vf24, vf28x\n"
                             "vmadday.xyzw ACC, vf25, vf28y\n"
                             "vmaddaz.xyzw ACC, vf26, vf28z\n"
                             "vmaddw.xyzw vf29, vf00, vf28w\n"
                             "vsub.w vf29, vf29, vf29\n"
                             "vadd.w vf29, vf29, vf00\n"
                             "sqc2 vf24, 0x0(%0)\n"
                             "sqc2 vf25, 0x10(%0)\n"
                             "sqc2 vf26, 0x20(%0)\n"
                             "sqc2 vf29, 0x30(%0)\n"
                             : : "r"(dst), "r"(src) : "$8", "$9", "$10", "$11", "$12", "$13", "$14", "$15", "memory");
        src += 0x40;
        dst += 0x40;
    }
}
