typedef float Vector[4] __attribute__((aligned(16)));

typedef struct {
    Vector rotation;
    Vector color;
    float brightness;
    float scale;
    float absBrightness;
    int flags;
    char p30[0x10];
} GlobalLight;

typedef struct {
    char p0[0x10];
    Vector direction;
    Vector color;
    int type;
    float p34;
    float brightness;
} WorkLightClass;

typedef struct {
    char p0[0x240];
    GlobalLight lights[3];
} LightWork;

extern WorkLightClass *GetNextWorkLightClass(LightWork *);

static inline void rotationToDirection(float *out, float *q)
{
    __asm__ __volatile__(
        "lqc2 vf4, 0(%1)\n"
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
        "sqc2 vf6, 0(%0)\n"
        : : "r"(out), "r"(q) : "memory");
}

static inline void scaleXYZ(float *out, float *a, float s)
{
    __asm__ __volatile__(
        "lqc2 vf5, 0(%1)\n" "qmtc2.ni %2, vf6\n"
        "vmulx.xyz vf5, vf5, vf6x\n" "sqc2 vf5, 0(%0)\n"
        : : "r"(out), "r"(a), "r"(s) : "memory");
}

void SetWorkFromGlobalLight(LightWork *w)
{
    int i;
    GlobalLight *light;
    WorkLightClass *c;
    float f;

    for (light = w->lights, i = 0; i < 3; i++, light++) {
        c = GetNextWorkLightClass(w);
        if (c != 0) {
            c->type = 2;
            if (light->flags & 0x1000) {
                c->type = 0x102;
            }
            rotationToDirection(c->direction, light->rotation);
            c->p34 = 0.0f;
            scaleXYZ(c->color, light->color, light->scale);
            f = light->absBrightness;
            if (f < 0.0f) {
                f = -f;
            }
            c->brightness = f;
        }
    }
}
