/* Serialized configuration words hold either scalar floats or encoded references.
 * Keep both views in the word type when resolving references across work stores. */
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

extern ResourceTable *DldSysUndefSymbol;
extern char *GetCharacterClass(void *object);
extern char *GetLayoutClass(void *object);
extern void setAttainRadPathWork(void *path, float radius);
extern void _setStopCtrlModeBaseMoveWork(void *work, int resource);
extern void func_00112FC8(void *object, void *work);

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

typedef union { unsigned int word; float scalar; void *pointer; } ConfigWord;

typedef struct {
    ResourceRef stop;
    ConfigWord parameter;
    ConfigWord acceleration;
    ConfigWord speed;
    ConfigWord friction;
    ConfigWord gravity;
    ConfigWord turn;
    ConfigWord extra;
    ResourceRef primary;
    ResourceRef secondary;
} WormConfig;

typedef struct {
    char pad0[0x54];
    float parameter;
    float acceleration;
    float speed;
    float friction;
    float gravity;
    float turn;
    int stop;
    float radius;
    char pad74[8];
    float extra;
    void *primary;
    void *secondary;
    char pad88[0x30];
    int unknownB8;
    int mode;
    int unknownC0;
    int unknownC4;
    int unknownC8;
    float height;
    int unknownD0;
    int unknownD4;
    char padD8[0x10];
    int burying;
    int type;
    int collisionJudge;
} WormWork;

void createWormCtrlWork(void *object, WormWork *work, ResourceRef *reference, void *path)
{
    WormConfig *config = resourceData(reference);
    *(char *)(GetCharacterClass(object) + 0xA25) = 2;
    *(char *)(GetCharacterClass(object) + 0xB20) = 1;
    setAttainRadPathWork(path, 3.1415926f);
    work->acceleration = config->acceleration.scalar;
    work->speed = config->speed.scalar;
    work->friction = config->friction.scalar;
    work->gravity = config->gravity.scalar;
    work->turn = config->turn.scalar;
    _setStopCtrlModeBaseMoveWork(work, (int)resourceElement(&config->stop));
    work->stop = 0;
    work->radius = 1.5707963f;
    work->parameter = config->parameter.scalar;
    work->extra = config->extra.scalar;
    work->type = 0;
    work->collisionJudge = 0;
    work->primary = resourceElement(&config->primary);
    work->secondary = resourceElement(&config->secondary);
    work->unknownB8 = 0;
    work->unknownD4 = 0;
    work->burying = 0;
    if (work->mode != 4) {
        work->height = *(float *)(*(char **)(GetLayoutClass(object) + 0x134) + 4);
    }
    work->unknownC8 = 0;
    work->mode = 0;
    work->unknownC0 = 0;
    work->unknownC4 = 0;
    func_00112FC8(object, work);
}
