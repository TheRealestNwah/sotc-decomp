extern char *GetCharacterClass(void *);
extern char *GAMEUTIL_get_motion_kind(void *);
extern int GAMEUTIL_get_node_quaternion_posi_by_id(float *, float *, void *, int);
extern void GAMEUTIL_get_local_directionZ(float *, void *);
extern int *SkelFocusDef_PLAYER_HEAD;

static inline int get_character_type(void *actor)
{
    char *c;
    if (actor != 0) {
        c = GetCharacterClass(actor);
        if (c != 0)
            return *(short *)(c + 0x370);
    }
    return -1000000;
}

int GAMEUTIL_get_player_look_around_direction(float *out, void *obj)
{
    float q[4] __attribute__((aligned(16)));
    float pos[4] __attribute__((aligned(16)));
    int t = get_character_type(obj) ^ 2;
    int isPlayer = t == 0;
    char *mk;
    int flag;
    int r;

    if (t == 0) {
        mk = GAMEUTIL_get_motion_kind(obj);
        if (mk != 0) {
            flag = (*(unsigned int *)(mk + 0x68) >> 28) & 1;
            if (flag == isPlayer) {
                r = GAMEUTIL_get_node_quaternion_posi_by_id(q, pos, obj, SkelFocusDef_PLAYER_HEAD[2]);
                if (r == flag) {
                    __asm__ __volatile__("lqc2 vf04, 0(%1)\n"
                                         "vmul.xyzw vf05, vf04, vf04\n"
                                         "vmr32.xyzw vf06, vf04\n"
                                         "vmul.xyzw vf07, vf06, vf04\n"
                                         "vaddy.z vf06, vf00, vf07y\n"
                                         "vsubw.z vf06, vf06, vf07w\n"
                                         "vsubx.y vf06, vf00, vf05x\n"
                                         "vsubz.y vf06, vf06, vf05z\n"
                                         "vaddz.x vf06, vf07, vf07z\n"
                                         "vsub.w vf06, vf00, vf00\n"
                                         "vadd.w vf05, vf00, vf00\n"
                                         "vmulw.xyz vf06, vf06, vf05w\n"
                                         "vaddw.y vf06, vf06, vf00w\n"
                                         "sqc2 vf06, 0(%0)\n"
                                         : : "r"(out), "r"(q) : "memory");
                    return r;
                }
            }
        }
    }
    GAMEUTIL_get_local_directionZ(out, obj);
    return 0;
}
