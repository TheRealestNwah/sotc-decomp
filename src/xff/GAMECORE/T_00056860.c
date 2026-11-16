/* Guard B bowgun shot: reads the bowgun node's quaternion and position, turns
   the quaternion into a direction with VU0 (w = 1) and fires the arrow. */
typedef struct {
    char p0[8];
    int id;
} GameObj;

typedef struct {
    float x, y, z, w;
} Vec;

extern GameObj *SkelFocusDef_Guard_B_Bowgun;
extern void GetMotionNodeQuaternionPos(void *, void *, void *, int, int);
extern void SCRSetupArrow1ByPlayer2(void *, int, void *, void *);

static void T_00056860(void *character)
{
    struct {
        Vec pos;
        Vec rot;
        Vec q;
    } L __attribute__((aligned(16)));

    GetMotionNodeQuaternionPos(&L.q, &L.pos, character, SkelFocusDef_Guard_B_Bowgun->id, 1);
    __asm__ __volatile__("lqc2 vf4, 0x0(%0)\n"
                         "vmul.xyzw vf5, vf4, vf4\n"
                         "vmr32.xyzw vf6, vf4\n"
                         "vmul.xyzw vf7, vf6, vf4\n"
                         "vmr32.xyzw vf6, vf6\n"
                         "vmul.xyzw vf8, vf6, vf4\n"
                         "vsubx.z vf6, vf0, vf5x\n"
                         "vsuby.z vf6, vf6, vf5y\n"
                         "vaddw.y vf6, vf7, vf7w\n"
                         "vsuby.x vf6, vf8, vf8y\n"
                         "vsub.w vf6, vf0, vf0\n"
                         "vadd.w vf5, vf0, vf0\n"
                         "vmulw.xyz vf6, vf6, vf5w\n"
                         "vaddw.z vf6, vf6, vf0w\n"
                         "sqc2 vf6, 0x0(%1)\n"
                         :
                         : "r"(&L.q), "r"(&L.rot)
                         : "memory");
    L.rot.w = 1.0f;
    SCRSetupArrow1ByPlayer2(character, 4, &L.rot, &L.pos);
}
