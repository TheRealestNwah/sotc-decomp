typedef struct {
    char *mot;
    int a;
    float b;
    float c;
    int pad10;
    int pad14;
    int d;
    float e;
    int f;
    int g;
    float ratio;
    float inv;
    char table[1];
} AnimClass;

typedef int Quadword __attribute__((mode(TI)));
typedef struct { Quadword q; } Vector;
typedef struct CameraAnimation {
    int id;
    AnimClass animation;
    char animationReserved[0x40 - sizeof(AnimClass)];
    int field44, geometryReference, reserved4C;
    char geometry[0x40];
    Vector position;
    int callbackActive;
    void (*callback)(void *);
    void *callbackArg;
    int fieldAC, fieldB0, fieldB4;
    char reservedB8[8];
} CameraAnimation;
extern CameraAnimation B_0015DBD0[10];
extern unsigned char InitialGeometryPointer[];
extern Vector ZeroPoint;
extern void InitAnimationClass(AnimClass *, char *);
extern void CopyGeometryPointer(void *, void *);

static inline void resetCameraAnimation(CameraAnimation *entry)
{
    entry->id = 0;
    InitAnimationClass(&entry->animation, 0);
    entry->field44 = 0;
    entry->geometryReference = 0;
    CopyGeometryPointer(entry->geometry, InitialGeometryPointer);
    entry->position = ZeroPoint;
    entry->callbackActive = 0;
    entry->callback = 0;
    entry->callbackArg = 0;
    entry->fieldAC = 0;
    entry->fieldB0 = 0;
    entry->fieldB4 = 0;
}

static inline void stopCameraAnimation(CameraAnimation *entry)
{
    if (entry->callbackActive && entry->callback)
        entry->callback(entry->callbackArg);
    resetCameraAnimation(entry);
}

static void *func_000E7758(int);

void *get_main_type_camera_lws_animation(void)
{
    return func_000E7758(0);
}

void *get_interest_type_camera_lws_animation(void)
{
    return func_000E7758(2);
}

void *get_fixed_point_type_camera_lws_animation(void)
{
    return func_000E7758(3);
}

int end_camera_lws_animation(unsigned int index)
{
    if (index < 10) {
        stopCameraAnimation(&B_0015DBD0[index]);
        return 1;
    }
    return 0;
}

int end_camera_lws_animation_by_paramID(int id)
{
    int i;
    for (i = 0; i < 10; i++) {
        CameraAnimation *entry = &B_0015DBD0[i];
        if (entry->id == id) {
            stopCameraAnimation(entry);
            return 1;
        }
    }
    return 0;
}

void init_camera_lws_animation_manager(void)
{
    int i;
    for (i = 0; i < 10; i++)
        resetCameraAnimation(&B_0015DBD0[i]);
}

static void *func_000E7758(int mode)
{
    CameraAnimation *entry = B_0015DBD0;
    int i;
    for (i = 0; i < 10; i++, entry++) {
        if (entry->id != 0 && ((*(unsigned int *)((char *)entry->id + 0x10) >> 3) & 7) == mode)
            return entry;
    }
    return 0;
}
static int func_000E77A8(void)
{
    int count = 0;
    int i;
    for (i = 0; i < 10; i++) {
        if (B_0015DBD0[i].id != 0)
            count++;
    }
    return count;
}
