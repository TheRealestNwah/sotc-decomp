typedef int s128 __attribute__((mode(TI)));
typedef struct { float v[4]; } __attribute__((aligned(8))) V4;
typedef struct {
    char pad0[0x134];
    s128 *pos;
} Layout;

extern char rootPtn[], gcGlobalVar[], ZeroPoint[];
extern void *DldSysUndefSymbol;
extern int SH_GameObjectLEO[];
extern char *StageLayout_TORCH_FALL_ANIM;
extern char *SkelFocusDef_PLAYER_SWORD;
extern char *GetSCRCharaAIWorkPtr(int);
extern Layout *GetLayoutClass(int);
extern char *GetCharacterClass(int);
extern void isysRequestDeleteObj(int);
extern void GetQuaternionByDegEulerYXZ(void *, float, float, float);
extern void GetMotionNodeQuaternionPos(void *, void *, int, int, int);
extern int ClipCollisionFinder(void *, void *, void *, void *);
extern int loadObj(char *, void *, void *, void *, int, int);

static inline char *resourceData(unsigned int *reference)
{
    unsigned int encoded = *reference;
    unsigned int offset = encoded & 0x3FFFF;
    char *module;
    if (offset)
        module = *(char **)((char *)reference - offset);
    else
        module = 0;
    if (module && module != DldSysUndefSymbol) {
        int index = (encoded >> 18) & 0xFFF;
        return *(char **)(module + 0x10) + index * *(int *)(*(char **)(module + 8) + 0xC);
    }
    return 0;
}

/* Deletes the previous torch-fall object, then spawns the TORCH_FALL_ANIM layout object at the player's sword node
   (or the layout position when the collision clip finds the path blocked). */
static void func_0007A670(int obj)
{
    int req[16];
    float p[4] __attribute__((aligned(16)));
    float q[4] __attribute__((aligned(16)));
    float scale[4] __attribute__((aligned(16)));
    float quat[4] __attribute__((aligned(16)));
    V4 pos2;
    V4 pos;
    char buf[0x50] __attribute__((aligned(16)));
    char *w = GetSCRCharaAIWorkPtr(obj);
    char *s;
    char *ch;
    Layout *lay;

    if (*(int *)(w + 0x150)) {
        isysRequestDeleteObj(*(int *)(w + 0x150));
        *(int *)(w + 0x150) = 0;
    }
    if (DldSysUndefSymbol == SH_GameObjectLEO)
        return;
    pos.v[0] = *(float *)(StageLayout_TORCH_FALL_ANIM + 0x30);
    pos.v[1] = *(float *)(StageLayout_TORCH_FALL_ANIM + 0x34);
    pos.v[2] = *(float *)(StageLayout_TORCH_FALL_ANIM + 0x38);
    pos.v[3] = 1.0f;
    pos2 = pos;
    scale[0] = -*(float *)(StageLayout_TORCH_FALL_ANIM + 0x18);
    scale[1] = *(float *)(StageLayout_TORCH_FALL_ANIM + 0x1C);
    scale[2] = -*(float *)(StageLayout_TORCH_FALL_ANIM + 0x20);
    scale[3] = 1.0f;
    GetQuaternionByDegEulerYXZ(quat, *(float *)(StageLayout_TORCH_FALL_ANIM + 0x24), -*(float *)(StageLayout_TORCH_FALL_ANIM + 0x28), *(float *)(StageLayout_TORCH_FALL_ANIM + 0x2C));
    req[1] = (int)scale;
    req[2] = (int)quat;
    req[3] = (int)&pos2;
    req[0] = 0;
    req[8] = 0;
    req[4] = *(int *)(StageLayout_TORCH_FALL_ANIM + 8);
    req[5] = (int)resourceData((unsigned int *)(StageLayout_TORCH_FALL_ANIM + 0x3C));
    ((union { int i; float f; } *)&req[6])->f = *(float *)(StageLayout_TORCH_FALL_ANIM + 0x40);
    req[7] = *(int *)(StageLayout_TORCH_FALL_ANIM + 0x44);
    req[9] = 0;
    req[10] = 0;
    req[11] = 1;
    req[12] = *(int *)(StageLayout_TORCH_FALL_ANIM + 0x14);
    req[13] = 0;
    req[14] = 0;
    GetMotionNodeQuaternionPos(q, p, obj, *(int *)(SkelFocusDef_PLAYER_SWORD + 8), 1);
    lay = GetLayoutClass(obj);
    ch = GetCharacterClass(obj);
    if (ClipCollisionFinder(buf, lay->pos, p, ch + 0xE20))
        *(s128 *)p = *GetLayoutClass(obj)->pos;
    req[0] = (int)ZeroPoint;
    req[1] = (int)p;
    req[2] = (int)q;
    req[4] = 1;
    *(float *)&req[6] = 5.0f;
    *(int *)(w + 0x150) = loadObj(StageLayout_TORCH_FALL_ANIM + 4, req, rootPtn, gcGlobalVar + 0x280, 0, 4);
}
