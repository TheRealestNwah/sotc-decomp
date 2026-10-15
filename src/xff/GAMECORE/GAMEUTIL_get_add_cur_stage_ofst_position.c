typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; int i[4]; } Vec4;
extern void *get_main_cameraman_camera_obj(void);
extern void *get_camera_position(void *);
extern void GetStageCenter(Vec4 *, void *);

void GAMEUTIL_get_add_cur_stage_ofst_position(Vec4 *out, Vec4 *ofs)
{
    Vec4 c;
    GetStageCenter(&c, get_camera_position(get_main_cameraman_camera_obj()));
    __asm__ __volatile__("lqc2 vf05, 0(%1)\n"
                         "lqc2 vf06, 0(%2)\n"
                         "vadd.xyz vf05, vf05, vf06\n"
                         "sqc2 vf05, 0(%0)\n"
                         : : "r"(out), "r"(ofs), "r"(&c) : "memory");
}
