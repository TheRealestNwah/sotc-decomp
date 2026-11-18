typedef int s128 __attribute__((mode(TI)));

typedef struct {
    int unk0;
    int unk4;
    float unk8;
    int unkC;
    float scale;
    int unk14;
    char pad18[0x8];
    s128 pos;
    int unk30;
    char pad34[0xC];
    int unk40;
} GazeCtrlWork;

extern char *GetCharacterClass(int);
extern char *GetLayoutClass(int);
extern char *getPassageWork(char *, int);
extern char *getSCRDataCtrlWork(int);
extern int memcmp(const void *, const void *, int);
extern void GetScaleQuaternion(void *, void *, float);
extern void GetLimitationQuaternion(void *, void *, float);
extern void setExecGazeIKWork(char *, int);
extern void setGazeModeGazeIKWork(char *, int);
extern void setGazeDirGazeIKWork(char *, void *);
extern void updateGazeIKWork(char *, void *);
extern int equipmentInvisibilityCloak(char *);
extern int perceptionExec(int, char *, void *, void *);
extern s128 IdentityQuaternion;

static inline void quatMul(void *d, void *a, void *bb)
{
    register void *b __asm__("$3") = bb;
    __asm__ __volatile__("lqc2 vf11, 0x0(%1)\n"
                         "lqc2 vf12, 0x0(%2)\n"
                         "vmul.xyzw vf13, vf11, vf12\n"
                         "vaddy.x vf13, vf13, vf13y\n"
                         "vaddz.x vf13, vf13, vf13z\n"
                         "vsubx.w vf13, vf13, vf13x\n"
                         "vmulw.xyz vf14, vf12, vf11w\n"
                         "vmulw.xyz vf15, vf11, vf12w\n"
                         "vopmula.xyz ACC, vf12, vf11\n"
                         "vopmsub.xyz vf16, vf11, vf12\n"
                         "vadd.xyz vf13, vf14, vf15\n"
                         "vadd.xyz vf13, vf13, vf16\n"
                         "sqc2 vf13, 0x0(%0)\n"
                         : : "r"(d), "r"(a), "r"(b) : "memory");
}

static inline void quatToDir(void *d, void *q)
{
    __asm__ __volatile__("lqc2 vf4, 0x0(%1)\n"
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
                         "sqc2 vf6, 0x0(%0)\n"
                         : : "r"(d), "r"(q) : "memory");
}

static inline float distanceXYZ(void *a, void *b)
{
    float len;

    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "vmul.xyz vf7, vf7, vf7\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         "vsqrt Q, vf7w\n"
                         "vwaitq\n"
                         "cfc2 $2, $vi22\n"
                         "mtc1 $2, %0\n"
                         : "=f"(len) : "r"(a), "r"(b) : "$2");
    return len;
}

void updateGazeCtrlWork(int chara, GazeCtrlWork *w, char *arg2, char *arg3)
{
    s128 target[1];
    s128 dir[1];
    s128 tmp[1];
    char *chr;
    char *p0;
    char *p1;
    char *scr;
    char *p;
    char *q;
    char *e;
    s128 *head;
    int flag = 0;

    chr = GetCharacterClass(chara);
    p0 = getPassageWork(arg2, 0);
    p1 = getPassageWork(arg2, 1);
    head = *(s128 **)(chr + 0x110C);
    if (head == 0) {
        return;
    }
    if (w->unk30 != 0 && w->unk40 == 0) {
        w->unk30 = 0;
    }
    if (w->unk0 == 0) {
        setExecGazeIKWork(chr, 0);
        return;
    }
    if (w->unkC != 0) {
        scr = getSCRDataCtrlWork(chara);
        p = scr + 0x3D10;
        switch (*(int *)(scr + 0x4090)) {
        case 4:
            p = scr + 0x3DC0;
        case 2:
            break;
        default:
            return;
        }
        q = p + 0x260;
        if (memcmp(q, &IdentityQuaternion, 0x10) != 0) {
            GetScaleQuaternion(tmp, q, w->scale);
            GetLimitationQuaternion(tmp, tmp, 1.3962634f);
            quatMul(tmp, tmp, *(char **)(chr + 0x13C));
            quatToDir(dir, tmp);
            setExecGazeIKWork(chr, 1);
            setGazeModeGazeIKWork(chr, 1);
            setGazeDirGazeIKWork(chr, dir);
        } else {
            setExecGazeIKWork(chr, 1);
            setGazeModeGazeIKWork(chr, 2);
        }
        return;
    }
    setGazeModeGazeIKWork(chr, 0);
    if (w->unk14 != 0) {
        if (w->unk30 != 0) {
            *target = **(s128 **)(GetLayoutClass(w->unk30) + 0x134);
        } else {
            *target = w->pos;
        }
        flag = 1;
    } else if (p0 != 0) {
        if (p1 != 0 && distanceXYZ(*(char **)(chr + 0x134), p0) < w->unk8) {
            *target = *(s128 *)p1;
        } else {
            *target = *(s128 *)p0;
        }
    } else {
        if (*(int *)(arg2 + 0x94) != 0 && *(int *)(arg2 + 0x3A0) == 0) {
            *target = **(s128 **)(*(char **)(arg3 + 0x4C) + 0x134);
        } else {
            *target = *head;
        }
        flag = 1;
    }
    e = *(char **)(arg3 + 0x4C);
    if (w->unk4 == 0) {
        if (distanceXYZ(target, *(char **)(e + 0x134)) < 0.1f && equipmentInvisibilityCloak(e) != 0) {
            setExecGazeIKWork(chr, 0);
        } else {
            setExecGazeIKWork(chr, 1);
        }
        updateGazeIKWork(chr, target);
        return;
    }
    if (distanceXYZ(target, *(char **)(e + 0x134)) < 0.1f) {
        if (*(float *)(arg3 + 0x28) < 0.0f && equipmentInvisibilityCloak(e) == 0) {
            setExecGazeIKWork(chr, 1);
        } else {
            setExecGazeIKWork(chr, 0);
        }
        updateGazeIKWork(chr, arg3);
        return;
    }
    if (flag != 0) {
        perceptionExec(chara, arg3, dir, target);
        if (perceptionExec(chara, arg3, dir, target) != 0) {
            setExecGazeIKWork(chr, 1);
        } else {
            setExecGazeIKWork(chr, 0);
        }
    } else {
        setExecGazeIKWork(chr, 1);
    }
    updateGazeIKWork(chr, target);
}
