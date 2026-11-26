typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;

typedef struct {
    char unknown00[8];
    unsigned int unknown08_0 : 18;
    unsigned int param : 10;
    unsigned int unknown08_28 : 4;
} SoundSource;

typedef struct {
    char unknown00[0x44];
    SoundSource *source;
} Sound3D;

typedef struct {
    float inner;
    float mid;
    float outer;
} SeParam;

typedef struct {
    char unknown00[8];
    int file;
} SeParamFile;

extern SeParamFile *EditWorkDefaultFile_seParam;
extern char *getEditWorkInitData(int);
extern void iosInverseMatrix(void *, void *);
extern void iosApplyRotMatrix(Vec4 *, void *, Vec4 *);
extern void iosGetStabXZVector(Vec4 *, Vec4 *);
extern void sndSepSetVol(Sound3D *, float);
extern void sndSepSetPan(Sound3D *, float);

void sound3DCalc(Sound3D *s, Vec4 *pos, Vec4 *cam, void *mtx)
{
    Vec4 d;
    Vec4 dir;
    float dist2;
    SeParam *p;
    float a, b, c, min, vol, pan;
    int idx = s->source->param;

    p = (SeParam *)(getEditWorkInitData(EditWorkDefaultFile_seParam->file) + idx * 12);
    if (cam == 0)
        return;
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(&d), "r"(pos), "r"(cam) : "memory");
    __asm__ __volatile__("lqc2 vf7, 0x0(%1)\n"
                         "vmul.xyz vf7, vf7, vf7\n"
                         "vaddy.x vf7, vf7, vf7y\n"
                         "vaddz.x vf7, vf7, vf7z\n"
                         "qmfc2 $2, vf7\n"
                         "mtc1 $2, %0\n"
                         : "=f"(dist2) : "r"(&d) : "$2");
    iosInverseMatrix(mtx, mtx);
    iosApplyRotMatrix(&dir, mtx, &d);
    iosGetStabXZVector(&dir, &dir);
    a = p->inner * p->inner;
    b = p->mid * p->mid;
    c = p->outer * p->outer;
    min = (a < b) ? a : b;
    if (dist2 < min) {
        vol = 1.0f;
    } else if (dist2 < b || c == 0.0f) {
        vol = 1.0f / (dist2 / b + 1.0f);
    } else if (!(dist2 < c)) {
        vol = 0.0f;
    } else {
        vol = 0.0f;
        if (!(c <= b))
            vol = 1.0f / ((dist2 - b) / (c = c - b) + 1.0f) - 0.5f;
    }
    if (p->inner < 0.0f)
        vol = 1.0f - vol;
    pan = dir.f[0];
    sndSepSetVol(s, vol);
    sndSepSetPan(s, pan);
}
