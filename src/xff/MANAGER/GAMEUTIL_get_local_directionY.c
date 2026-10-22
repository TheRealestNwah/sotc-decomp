extern void *GetCharacterClass(void *);
extern void *GetLayoutClass(void *);

typedef int s128 __attribute__((mode(TI)));
#define NULL ((void *)0)
void GAMEUTIL_get_local_directionY(void *out, void *arg1) { 
    s128 quaternion;
    s128 var_v0;
    void *temp_v0;

    temp_v0 = GetCharacterClass(arg1);
    if (temp_v0 != NULL) {
        var_v0 = (*(s128 *)((char *)(temp_v0) + 0x470));
    } else {
        var_v0 = *(*(s128 **)((char *)(GetLayoutClass(arg1)) + 0x13C));
    }
    quaternion = var_v0;
    __asm__ __volatile__(".set noreorder\n"
        "lqc2 vf4, 0x0(%1)\n"
        "vmul.xyzw vf5, vf4, vf4\n"
        "vmr32.xyzw vf6, vf4\n"
        "vmul.xyzw vf7, vf6, vf4\n"
        "vaddy.z vf6, vf0, vf7y\n"
        "vsubw.z vf6, vf6, vf7w\n"
        "vsubx.y vf6, vf0, vf5x\n"
        "vsubz.y vf6, vf6, vf5z\n"
        "vaddz.x vf6, vf7, vf7z\n"
        "vsub.w vf6, vf0, vf0\n"
        "vadd.w vf5, vf0, vf0\n"
        "vmulw.xyz vf6, vf6, vf5w\n"
        "vaddw.y vf6, vf6, vf0w\n"
        "sqc2 vf6, 0x0(%0)\n"
        ".set reorder\n"
        : : "r"(out), "r"(&quaternion) : "memory");
}
