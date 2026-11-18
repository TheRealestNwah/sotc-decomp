#ifdef NONMATCHING /* 5 diffs: the Original hoists only %hi(D_00139F40) and uses %lo in the lw/sw; ours hoists the full address */
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
extern int D_00139F40;
extern void *func_000E7758(int);
extern char *initAnimationObjResource(void *);
extern void InitAnimationClassWithFrame(AnimClass *, char *, float);
extern void CopyGeometryPointer(void *, void *);
extern void GetGeometryPointerPosition(Vector *, void *);

typedef struct { char pad[0x10]; unsigned int lo:3; unsigned int type:3; } AnimObj;

static int boot_camera_lws_animation(AnimObj *anim, void *geo, void (*cb)(void *), void *arg, int ac, float frame)
{
    CameraAnimation *e;
    char *res;
    int isMain;
    int i;

    if (anim == 0)
        return -1;
    isMain = anim->type == 0;
    if (anim->type == 0 && func_000E7758(0))
        return -1;
    if ((anim->type ^ 2) == 0 && func_000E7758(2))
        return -1;
    if ((anim->type ^ 3) == 0 && func_000E7758(3))
        return -1;
    for (i = 0, e = B_0015DBD0; i < 10; i++, e++) {
        if (e->id == 0) {
            { int d = D_00139F40; if (isMain == 1) d = isMain; D_00139F40 = d; }
            res = initAnimationObjResource((char *)anim + 4);
            if (res != 0) {
                e->id = (int)anim;
                InitAnimationClassWithFrame(&e->animation, 0, frame);
                e->field44 = *(int *)(res + 0x20);
                CopyGeometryPointer(e->geometry, geo);
                e->geometryReference = 1;
                GetGeometryPointerPosition(&e->position, e->geometry);
                e->callbackActive = 1;
                e->callback = cb;
                e->callbackArg = arg;
                e->fieldAC = ac;
                e->fieldB0 = 0;
                e->fieldB4 = 0;
            }
            return i;
        }
    }
    return -1;
}
#endif
