typedef struct {
    char pad00[0x18];
    float f18;
    float f1C;
    char pad20[0x44 - 0x20];
    float f44;
    float f48;
    char pad4C[0x50 - 0x4C];
    float f50;
} DefB9B00;

typedef struct {
    char pad00[0xE8];
    float fE8;
    char padEC[0x120 - 0xEC];
    float f120;
    char pad124[0x170 - 0x124];
    int state;
    char pad174[0x190 - 0x174];
    float f190;
    float f194;
    char pad198[0x210 - 0x198];
    char b210[0x260 - 0x210];
    float f260;
} ObjB9B00;

extern float iosGetRandom(void);
extern void *isysGetThisSubThread(void);
extern void func_000B91C0(ObjB9B00 *, float, float);
extern void func_000B9548(ObjB9B00 *, float, void *, float);
extern void AI_GetRandomVelocity(float *, void *, void *, float, float, float, float);

#define DEF(o) (*(DefB9B00 **)((char *)(o) + 0x64))

static void func_000B9B00(ObjB9B00 *o)
{
    float v;
    float a;
    float hi;
    float lo;
    float r;
    float r1;

    if (o->fE8 >= 0.0f) {
        if (o->f120 < 0.0f) {
            v = 1.0f - -o->f120 * 0.5f;
        } else {
            v = 1.0f - o->f120 * 0.5f;
        }
    } else {
        a = o->f120;
        if (a < 0.0f) {
            a = -a;
        }
        v = a * 0.5f;
    }
    hi = v * DEF(o)->f50;
    lo = (1.0f - v) * DEF(o)->f50;
    r1 = iosGetRandom() * 5.0f;
    r = iosGetRandom();
    isysGetThisSubThread();
    if (o->f190 < o->f194) {
        if (r < hi) {
            o->state = 0x11;
        } else if (r < hi + lo) {
            o->state = 0x12;
        } else {
            o->state = 0x10;
        }
        o->f190 = r1;
        o->f194 = 0.0f;
    }
    func_000B91C0(o, DEF(o)->f44, 1.0f);
    AI_GetRandomVelocity(&o->f260, (char *)o + 0x198, (char *)o + 0x19C, DEF(o)->f18, DEF(o)->f1C, 1.0f, DEF(o)->f48);
    func_000B9548(o, o->f260, o->b210, *(float *)((char *)o + 0x23C));
}
