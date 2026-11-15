/* Parked: 5 diffs, same size (124 words). Knight arm/neck break: starts the PARTS LWS, rebuilds each break part's geometry from the node quaternion (15-instruction VU0 run turning the quaternion into a basis, `vmr32`/`vmul` chain, run twice) and starts the BREAK LWS, then sets the game flags. One local struct {pos, rot, q} pins the frame (pos +0, rot +0x10, q +0x20). Remaining: v0/v1 choice for the SkelFocusDef_KNIGHT_NECK load and the last two GameObject lookups (hi/lo register swap). */
#ifdef NONMATCHING
typedef struct {
    char p0[8];
    int id;
} GameObj;

typedef struct {
    float x, y, z, w;
} Vec;

extern GameObj *GameObject_KNIGHT_ARM_BREAK;
extern GameObj *GameObject_KNIGHT_ARM_PARTS;
extern GameObj *GameObject_KNIGHT_NECK_PARTS;
extern GameObj *GameObject_KNIGHT_NECK_BREAK;
extern GameObj *SkelFocusDef_KNIGHT_UDE_R;
extern GameObj *SkelFocusDef_KNIGHT_NECK;
extern char YUnitVector[];
extern int chkGameFlagForGameObj(int);
extern int setGameFlagForGameObj(int);
extern void _SCRStartLWS(int, int, int, int);
extern void GetMotionNodeQuaternionPos(void *, void *, void *, int, int);
extern void StabilizeToYRotQuaternion(void *);
extern void SCRSetLWSGeometryWithZY(int, int, void *, void *, void *);

void func_000631A0(void *character)
{
    struct {
        Vec pos;
        Vec rot;
        Vec q;
    } L __attribute__((aligned(16)));

    if (chkGameFlagForGameObj(GameObject_KNIGHT_ARM_BREAK->id) == 0) {
        _SCRStartLWS(GameObject_KNIGHT_ARM_PARTS->id, -1, 6, 0);
        _SCRStartLWS(GameObject_KNIGHT_NECK_PARTS->id, -1, 6, 0);
        GetMotionNodeQuaternionPos(&L.q, &L.pos, character, SkelFocusDef_KNIGHT_UDE_R->id, 1);
        StabilizeToYRotQuaternion(&L.q);
        __asm__ __volatile__("lqc2 vf4, 0x0(%0)
"
                             "vmul.xyzw vf5, vf4, vf4
"
                             "vmr32.xyzw vf6, vf4
"
                             "vmul.xyzw vf7, vf6, vf4
"
                             "vmr32.xyzw vf6, vf6
"
                             "vmul.xyzw vf8, vf6, vf4
"
                             "vsubx.z vf6, vf0, vf5x
"
                             "vsuby.z vf6, vf6, vf5y
"
                             "vaddw.y vf6, vf7, vf7w
"
                             "vsuby.x vf6, vf8, vf8y
"
                             "vsub.w vf6, vf0, vf0
"
                             "vadd.w vf5, vf0, vf0
"
                             "vmulw.xyz vf6, vf6, vf5w
"
                             "vaddw.z vf6, vf6, vf0w
"
                             "sqc2 vf6, 0x0(%1)
"
                             :
                             : "r"(&L.q), "r"(&L.rot)
                             : "memory");
        SCRSetLWSGeometryWithZY(GameObject_KNIGHT_ARM_BREAK->id, 0, &L.pos, &L.rot, YUnitVector);
        GetMotionNodeQuaternionPos(&L.q, &L.pos, character, SkelFocusDef_KNIGHT_NECK->id, 0);
        StabilizeToYRotQuaternion(&L.q);
        __asm__ __volatile__("lqc2 vf4, 0x0(%0)
"
                             "vmul.xyzw vf5, vf4, vf4
"
                             "vmr32.xyzw vf6, vf4
"
                             "vmul.xyzw vf7, vf6, vf4
"
                             "vmr32.xyzw vf6, vf6
"
                             "vmul.xyzw vf8, vf6, vf4
"
                             "vsubx.z vf6, vf0, vf5x
"
                             "vsuby.z vf6, vf6, vf5y
"
                             "vaddw.y vf6, vf7, vf7w
"
                             "vsuby.x vf6, vf8, vf8y
"
                             "vsub.w vf6, vf0, vf0
"
                             "vadd.w vf5, vf0, vf0
"
                             "vmulw.xyz vf6, vf6, vf5w
"
                             "vaddw.z vf6, vf6, vf0w
"
                             "sqc2 vf6, 0x0(%1)
"
                             :
                             : "r"(&L.q), "r"(&L.rot)
                             : "memory");
        SCRSetLWSGeometryWithZY(GameObject_KNIGHT_NECK_BREAK->id, 0, &L.pos, &L.rot, YUnitVector);
        _SCRStartLWS(GameObject_KNIGHT_ARM_BREAK->id, -1, 6, 0);
        _SCRStartLWS(GameObject_KNIGHT_NECK_BREAK->id, -1, 6, 0);
        setGameFlagForGameObj(GameObject_KNIGHT_ARM_BREAK->id);
        setGameFlagForGameObj(GameObject_KNIGHT_NECK_BREAK->id);
    }
}
#endif
