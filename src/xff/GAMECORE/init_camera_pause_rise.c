typedef unsigned int Qword __attribute__((mode(TI)));
typedef union { Qword q; float f[4]; } Vector;
typedef struct {
    Vector position;
    Vector target;
    char pad20[0x10];
    float first;
    float second;
    float last;
} PauseParameters;
typedef struct {
    int state;
    int counter;
    char pad8[8];
    Vector position;
    Vector target;
    float first;
    float second;
    float height;
    float unknown3C;
    float last;
    float distance;
    float viewAngle;
} PauseRise;
extern float get_view_angle_camera_view_angle_cntrl(void *control);

static inline float distanceXZ(Vector *a, Vector *b)
{
    float distance;
    __asm__ __volatile__(
        "lqc2 vf5, 0(%1)\n"
        "lqc2 vf6, 0(%2)\n"
        "vsub.xyzw vf7, vf5, vf6\n"
        "vmul.xz vf7, vf7, vf7\n"
        "vaddz.x vf7, vf7, vf7z\n"
        "vsqrt Q, vf7x\n"
        "vwaitq\n"
        "cfc2 $2, $vi22\n"
        "mtc1 $2, %0\n"
        : "=f"(distance) : "r"(a), "r"(b) : "$2");
    return distance;
}

void init_camera_pause_rise(PauseRise *work, char *camera)
{
    PauseParameters *parameters = (PauseParameters *)(camera + 0x1490);
    work->state = 1;
    work->counter = 0;
    work->position.q = parameters->position.q;
    work->target.q = parameters->target.q;
    work->first = parameters->first;
    work->second = parameters->second;
    work->height = *(float *)(camera + 0x1534);
    work->unknown3C = 0.0f;
    work->last = parameters->last;
    work->distance = distanceXZ(&parameters->position, &parameters->target);
    work->viewAngle = get_view_angle_camera_view_angle_cntrl(camera + 0x1538);
}
