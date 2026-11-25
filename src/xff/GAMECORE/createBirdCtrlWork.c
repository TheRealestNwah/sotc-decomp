typedef union {
    unsigned int word;
    float scalar;
} ResourceRef;

typedef struct {
    char pad0[0xC];
    int stride;
} ResourceType;

typedef struct {
    char pad0[8];
    ResourceType *type;
    int unknown0C;
    char *data;
} ResourceTable;

typedef int s128 __attribute__((mode(TI)));

extern ResourceTable *DldSysUndefSymbol;
extern char *GetCharacterClass(void *object);
extern char *GetLayoutClass(void *object);
extern void setAttainRadPathWork(void *path, float radius);
extern void _setStopCtrlModeBaseMoveWork(void *work, int resource);
extern int GetMotionResourceFrames(void *motion);
extern float GetMotionStretchRatio(void *motion);
extern void analyzeMotionPropertyXZ(void *object, void *motion, float s, float t, float *a, float *b, int u);
extern void analyzeMotionProperty2(void *object, void *motion, float s, float t, float v, float *a, float *b, int u);
extern void GetMotionRootIntFrame(void *dst, void *motion, int frame);
extern void GetMotionIntFrame(void *dst, void *motion, int frame, int count);
extern void GetCharacterClassBaseQ(void *dst, void *src, void *chara);
extern void getTurnAndPitchFromQuaternion(void *q, float *turn, float *pitch);
extern void func_001037C0(void *object, void *work);

static inline ResourceTable *resourceTable(ResourceRef *reference)
{
    int offset = reference->word & 0x3FFFF;
    return offset ? *(ResourceTable **)((char *)reference - offset) : 0;
}

static inline void *resourceData(ResourceRef *reference)
{
    ResourceTable *table = resourceTable(reference);
    return table && table != DldSysUndefSymbol ? table->data : 0;
}

static inline void *resourceElement(ResourceRef *reference)
{
    ResourceTable *table = resourceTable(reference);
    return table && table != DldSysUndefSymbol
        ? table->data + ((reference->word >> 18) & 0xFFF) * table->type->stride : 0;
}

static inline void mulVec3(void *d, void *s)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                         "lqc2 vf6, 0x0(%1)\n"
                         "vmul.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         :
                         : "r"(d), "r"(s)
                         : "memory");
}

static inline void unitVec(void *d)
{
    __asm__ __volatile__("sqc2 vf0, 0x0(%0)\n" : : "r"(d) : "memory");
}

typedef union { unsigned int word; float scalar; void *pointer; } ConfigWord;

typedef struct {
    ResourceRef stop;
    ResourceRef motion;
    ConfigWord x8;
    ConfigWord xC;
    ConfigWord x10;
    ConfigWord x14;
    ConfigWord x18;
    ConfigWord x1C;
    ConfigWord x20;
    ConfigWord x24;
    ConfigWord x28;
    ResourceRef x2C;
    ResourceRef x30;
    ResourceRef x34;
    ConfigWord x38;
    ConfigWord x3C;
    ResourceRef x40;
    ResourceRef x44;
    ConfigWord x48;
    ConfigWord x4C;
    ConfigWord x50;
    ConfigWord x54;
    ConfigWord x58;
    ConfigWord x5C;
    ConfigWord x60;
    ConfigWord x64;
    ResourceRef x68;
} BirdConfig;

typedef struct {
    char pad0[0x64];
    void *x64;
    float x68;
    float x6C;
    float x70;
    float x74;
    float x78;
    float x7C;
    float x80;
    float x84;
    float x88;
    float x8C;
    float x90;
    float x94;
    float x98;
    float x9C;
    float xA0;
    float xA4;
    float xA8;
    float xAC;
    float xB0;
    float xB4;
    float xB8;
    void *xBC;
    char *xC0;
    float xC4;
    float xC8;
    float xCC;
    char *xD0;
    float xD4;
    float xD8;
    float xDC;
    float xE0;
    char padE4[0xC];
    s128 xF0;
    float x100;
    float x104;
    char pad108[8];
    s128 x110;
    s128 x120;
    int x130;
    char pad134[4];
    int x138;
    char pad13C[0x18];
    int x154;
    char pad158[8];
    s128 x160;
    s128 x170;
    s128 x180;
    int x190;
    float x194;
    float x198;
    float x19C;
    float x1A0;
    float x1A4;
    int x1A8;
    int x1AC;
    s128 x1B0;
    char *x1C0;
    char pad1C4[0xC];
    s128 x1D0;
    s128 x1E0;
    float x1F0;
    float x1F4;
    float x1F8;
    float x1FC;
    void *x200;
} BirdWork;

void createBirdCtrlWork(void *object, BirdWork *work, ResourceRef *reference, void *path)
{
    BirdConfig *config = resourceData(reference);
    char *motion;
    float q[4] __attribute__((aligned(16)));
    float ratio;
    float ratio2;
    float turn;
    float ratio3;
    int frames;

    setAttainRadPathWork(path, 3.1415926f);
    work->x68 = config->x8.scalar;
    work->x6C = config->xC.scalar;
    work->x70 = config->x10.scalar;
    work->x74 = work->x68;
    if (work->x74 < work->x6C) {
        work->x74 = work->x6C;
    }
    if (work->x74 < work->x70) {
        work->x74 = work->x70;
    }
    work->x78 = config->x14.scalar;
    _setStopCtrlModeBaseMoveWork(work, (int)resourceElement(&config->stop));
    work->x64 = resourceElement(&config->x40);
    work->x7C = config->x18.scalar;
    work->x80 = 0.0f;
    work->x84 = 0.0f;
    work->x88 = 0.0f;
    work->x90 = 0.0f;
    work->x94 = 0.0f;
    work->x8C = 0.0f;
    work->x98 = 0.0f;
    work->x9C = 0.0f;
    work->xA0 = 0.0f;
    work->xA8 = 0.0f;
    work->xB0 = config->x20.scalar;
    work->xB4 = config->x24.scalar;
    work->xB8 = config->x28.scalar;
    work->xBC = resourceElement(&config->x2C);
    work->xA4 = config->x1C.scalar * 0.017453293f;
    work->x1F0 = config->x4C.scalar * 0.017453293f;
    work->x1F4 = config->x50.scalar;
    work->x194 = config->x54.scalar;
    work->x198 = config->x58.scalar;
    work->x19C = config->x5C.scalar;
    work->x1A0 = config->x60.scalar;
    work->x1A4 = config->x64.scalar;
    motion = resourceElement(&config->motion);
    frames = GetMotionResourceFrames(motion + 0x50);
    work->xAC = (float)frames / GetMotionStretchRatio(motion + 0x50) / (float)*(int *)(motion + 0x5C);
    work->xC0 = resourceElement(&config->x34);
    analyzeMotionPropertyXZ(object, work->xC0, 1.0f, 0.0f, &work->xC8, &work->xC4, 0);
    analyzeMotionProperty2(object, work->xC0, 1.0f, 0.0f, 1.0f, &work->xCC, &ratio, 0);
    work->xCC /= ratio;
    work->x200 = resourceElement(&config->x68);
    work->xD0 = resourceElement(&config->x30);
    if (work->xD0) {
        analyzeMotionPropertyXZ(object, work->xD0, 1.0f, 0.0f, &work->xD8, &work->xD4, 0);
        analyzeMotionProperty2(object, work->xD0, 1.0f, 0.0f, 1.0f, &work->xDC, &ratio2, 0);
        work->xDC /= ratio2;
        work->xE0 = config->x38.scalar + work->xD8;
    } else {
        *(int *)&work->xD4 = 0;
        *(int *)&work->xD8 = 0;
        *(int *)&work->xDC = 0;
        *(int *)&work->xE0 = 0;
    }
    work->x100 = config->x3C.scalar;
    work->x104 = config->x38.scalar + work->xC8;
    GetMotionRootIntFrame(&work->xF0, work->xC0 + 0x50, GetMotionResourceFrames(work->xC0 + 0x50));
    mulVec3(&work->xF0, GetLayoutClass(object) + 0x90);
    func_001037C0(object, work);
    unitVec(&work->x110);
    unitVec(&work->x120);
    work->x130 = 0;
    work->x138 = 0;
    work->x154 = 0;
    unitVec(&work->x160);
    unitVec(&work->x170);
    unitVec(&work->x180);
    work->x190 = 0;
    work->x1A8 = 0;
    work->x1AC = 0;
    work->x1C0 = resourceElement(&config->x44);
    unitVec(&work->x1B0);
    if (work->x1C0) {
        char *layout = GetLayoutClass(object);
        s128 buf[*(short *)(layout + 0x1B4)];
        GetMotionRootIntFrame(&work->x1D0, work->x1C0 + 0x50, 0);
        mulVec3(&work->x1D0, GetLayoutClass(object) + 0x90);
        GetMotionRootIntFrame(&work->x1E0, work->x1C0 + 0x50, GetMotionResourceFrames(work->x1C0 + 0x50));
        mulVec3(&work->x1E0, GetLayoutClass(object) + 0x90);
        GetMotionIntFrame(buf, work->x1C0 + 0x50, 0, *(short *)(layout + 0x1B4));
        GetCharacterClassBaseQ(q, buf, GetCharacterClass(object));
        getTurnAndPitchFromQuaternion(q, &turn, &work->x1F8);
        analyzeMotionProperty2(object, work->x1C0, 1.0f, 0.0f, 1.0f, &work->x1FC, &ratio3, 0);
        work->x1FC /= ratio3;
    } else {
        work->x1F8 = 0.78539813f;
        work->x1FC = 20.0f;
    }
}
