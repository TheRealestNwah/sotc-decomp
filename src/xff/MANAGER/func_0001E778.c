typedef int s128 __attribute__((mode(TI)));

static int func_0001E778(char *, char *, int, int);

static int func_0001E778(char *tree, char *node, int flag, int depth)
{
    register int m_and __asm__("$4");
    register int m_or __asm__("$5");
    int v;
    register char *p10 __asm__("$2");

    if (flag == 0) {
        p10 = node + 0x10;
        __asm__ __volatile__(
                         "lqc2 vf1, 0x0(%2)
"
                         "lqc2 vf2, 0x0(%3)
"
                         "addiu %0, $0, 0x3F
"
                         "addiu %1, $0, 0
"
                         "vmove.xyz vf10, vf1
"
                         "vmove.x vf11, vf1
"
                         "vmove.yz vf11, vf2
"
                         "vmove.y vf15, vf2
"
                         "vmove.x vf16, vf2
"
                         "vmulax.xyzw ACC, vf4, vf10x
"
                         "vmadday.xyzw ACC, vf5, vf10y
"
                         "vmaddaz.xyzw ACC, vf6, vf10z
"
                         "vmaddw.xyzw vf20, vf7, vf0w
"
                         "vmove.y vf12, vf1
"
                         "vmove.xz vf12, vf2
"
                         "vmove.z vf13, vf1
"
                         ".word 0x4BD4A1FF
"
                         "vmulax.xyzw ACC, vf4, vf11x
"
                         "vmadday.xyzw ACC, vf5, vf11y
"
                         "vmaddaz.xyzw ACC, vf6, vf11z
"
                         "vmaddw.xyzw vf21, vf7, vf0w
"
                         "vmove.xy vf13, vf2
"
                         "cfc2.ni $3, $vi18
"
                         "and %0, %0, $3
"
                         "or %1, %1, $3
"
                         ".word 0x4BD5A9FF
"
                         "vmulax.xyzw ACC, vf4, vf12x
"
                         "vmadday.xyzw ACC, vf5, vf12y
"
                         "vmaddaz.xyzw ACC, vf6, vf12z
"
                         "vmaddw.xyzw vf20, vf7, vf0w
"
                         "vmove.xy vf14, vf1
"
                         "cfc2.ni $3, $vi18
"
                         "and %0, %0, $3
"
                         "or %1, %1, $3
"
                         ".word 0x4BD4A1FF
"
                         "vmulax.xyzw ACC, vf4, vf13x
"
                         "vmadday.xyzw ACC, vf5, vf13y
"
                         "vmaddaz.xyzw ACC, vf6, vf13z
"
                         "vmaddw.xyzw vf21, vf7, vf0w
"
                         "vmove.z vf14, vf2
"
                         "cfc2.ni $3, $vi18
"
                         "and %0, %0, $3
"
                         "or %1, %1, $3
"
                         ".word 0x4BD5A9FF
"
                         "vmulax.xyzw ACC, vf4, vf14x
"
                         "vmadday.xyzw ACC, vf5, vf14y
"
                         "vmaddaz.xyzw ACC, vf6, vf14z
"
                         "vmaddw.xyzw vf20, vf7, vf0w
"
                         "vmove.xz vf15, vf1
"
                         "cfc2.ni $3, $vi18
"
                         "and %0, %0, $3
"
                         "or %1, %1, $3
"
                         ".word 0x4BD4A1FF
"
                         "vmulax.xyzw ACC, vf4, vf15x
"
                         "vmadday.xyzw ACC, vf5, vf15y
"
                         "vmaddaz.xyzw ACC, vf6, vf15z
"
                         "vmaddw.xyzw vf21, vf7, vf0w
"
                         "vmove.yz vf16, vf1
"
                         "cfc2.ni $3, $vi18
"
                         "and %0, %0, $3
"
                         "or %1, %1, $3
"
                         ".word 0x4BD5A9FF
"
                         "vmulax.xyzw ACC, vf4, vf16x
"
                         "vmadday.xyzw ACC, vf5, vf16y
"
                         "vmaddaz.xyzw ACC, vf6, vf16z
"
                         "vmaddw.xyzw vf20, vf7, vf0w
"
                         "vmove.xyz vf17, vf2
"
                         "cfc2.ni $3, $vi18
"
                         "and %0, %0, $3
"
                         "or %1, %1, $3
"
                         ".word 0x4BD4A1FF
"
                         "vmulax.xyzw ACC, vf4, vf17x
"
                         "vmadday.xyzw ACC, vf5, vf17y
"
                         "vmaddaz.xyzw ACC, vf6, vf17z
"
                         "vmaddw.xyzw vf21, vf7, vf0w
"
                         "cfc2.ni $3, $vi18
"
                         "and %0, %0, $3
"
                         "or %1, %1, $3
"
                         ".word 0x4BD5A9FF
"
                         "vnop
"
                         "vnop
"
                         "vnop
"
                         "vnop
"
                         "vnop
"
                         "cfc2.ni $3, $vi18
"
                         "and %0, %0, $3
"
                         "or %1, %1, $3
"
                         : "=r"(m_and), "=r"(m_or) : "r"(node), "r"(p10) : "$3", "memory");
        v = m_or;
        if (m_and != 0) {
            *(int *)(node + 0x2C) = 1;
        } else if (v == 0) {
            *(int *)(node + 0x2C) = 2;
        } else {
            *(int *)(node + 0x2C) = 0;
        }
    } else {
        *(int *)(node + 0x2C) = flag;
    }
    if (depth == 0) {
        if (*(int *)(node + 0x2C) == 1)
            return 1;
    }
    v = *(int *)(node + 0x20);
    if (v != -1)
        func_0001E778(tree, tree + v * 48, *(int *)(node + 0x2C), depth + 1);
    v = *(int *)(node + 0x24);
    if (v != -1)
        func_0001E778(tree, tree + v * 48, *(int *)(node + 0x2C), depth + 1);
    return 0;
}
