typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;

extern char gcGlobalVar[];
extern char *GetCharacterClass(void *);
extern char *GetLayoutClass(void *);
extern int equipmentInvisibilityCloak(void);
extern void GetMotionNodeQuaternionPos(void *, void *, void *, int, int);
extern int SCRGetCollisionCallBack(void *, void *, void *, void *, int (*)(), int);
extern int func_00122CB8();

int perceptionExec2(void *obj, char *w, void *target)
{
    Vec4 pos;
    Vec4 quat;
    char *ch = GetCharacterClass(obj);
    char *lc = GetLayoutClass(obj);
    char *bone;

    if (equipmentInvisibilityCloak() != 0)
        return 0;
    bone = *(char **)(w + 0x44);
    if (bone != 0) {
        GetMotionNodeQuaternionPos(&quat, &pos, obj, *(int *)(bone + 8), 1);
    } else {
        quat.q = *(s128 *)(ch + 0x470);
        pos.q = **(s128 **)(lc + 0x134);
    }
    {
        char out[0x40];

        return SCRGetCollisionCallBack(out, &pos, target, gcGlobalVar + 0x250, func_00122CB8, 0) == 0;
    }
}
