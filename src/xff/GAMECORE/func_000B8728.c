typedef struct {
    char pad0[0x14];
    float x14;
    char pad18[0x30 - 0x18];
    float x30;
} AIParam;

typedef struct {
    char pad0[0x64];
    AIParam *param;
    char pad68[0x158 - 0x68];
    int x158;
    char pad15C[0x17C - 0x15C];
    int x17C;
    char pad180[0x210 - 0x180];
    float x210;
    float x214;
    float x218;
    char pad21C[0x264 - 0x21C];
    float x264;
} AIObj;

static void func_000B8728(AIObj *o)
{
    int m;
    float a;
    float b;
    float d;
    float e;
    float k14;
    float k30;

    m = o->x158;
    if (m == 2 || m == 6 || m == 8 || m == 9 || m == 10 || m == 11 || m == 13) {
        m = o->x17C;
        if (m == 30 || m == 31) {
            o->x210 = -o->x210;
            o->x218 = -o->x218;
        } else if (m == 28 || m == 29) {
            b = o->x210;
            a = o->x218;
            if (a < 0.0f) {
                a = -a;
            }
            o->x210 = a;
            if (m == 28) {
                o->x218 = -b;
            } else {
                o->x218 = b;
            }
        }
        o->x214 = 0.0f;
        a = o->x210;
        k30 = o->param->x30;
        k14 = o->param->x14;
        if (a < o->x214) {
            d = -a / k14;
        } else {
            d = a / k14;
        }
        if (a < 0.0f) {
            e = -a * k30;
        } else {
            e = a * k30;
        }
        o->x264 = d + e;
    }
}
