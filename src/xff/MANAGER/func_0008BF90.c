extern void *GetLayoutClass(void *);
extern void *GetGeometryPointerObject(void *);
extern char *GetCharacterClass(void *);
extern void func_0008BE00(unsigned char *, float, float);
extern void func_00088258(unsigned char *);

static inline char *GetObjWork(unsigned char *obj, int type)
{
    if (obj[8] == type) {
        return (char *)obj + 0x20;
    }
    return 0;
}

static int func_0008BF90(unsigned char *obj, float delta)
{
    char *w = GetObjWork(obj, 0xD);
    int ret = 0;
    float rate = 30.0f;
    char *anim;
    char *list;
    char *lc;
    void *geo;
    int *link;

    list = *(char **)(w + 0x328);
    lc = GetLayoutClass(obj);
    anim = w + 0x2E0;
    if (*(int *)(lc + 0x124) != 0)
        geo = GetGeometryPointerObject(lc + 0xC0);
    else
        geo = 0;
    if (geo != 0 && ((*(unsigned int *)(*(char **)(w + 0x32C) + 0x14) >> 8) & 1)) {
        char *cc = GetCharacterClass(geo);
        if (cc != 0) {
            float s = *(float *)(cc + 0x524);
            char *a = cc + 0x1C0;
            char *m = *(char **)a;
            float k = *(float *)(a + 0x1C);
            float t;
            if (m != 0) {
                register float x asm("$f0") = (float)*(int *)(m + 0x5C);
                t = x * *(float *)(cc + 0x374);
            } else {
                register float x asm("$f0") = *(float *)(cc + 0x374);
                t = x * 30.0f;
            }
            rate = t * k * s;
        }
    }
    *(float *)(anim + 0xC) = *(float *)(anim + 0x8);
    switch (*(signed char *)(w + 0x364)) {
    case 2:
    case 7:
        break;
    default:
        func_0008BE00(obj, rate, delta);
        break;
    case 3:
    case 4:
    case 6:
        func_0008BE00(obj, rate, delta);
        if (*(int *)(anim + 0x20) != 0) {
            float f = (float)(*(short *)(*(char **)(w + 0x334) + 4) - 1);
            *(float *)(anim + 0xC) = f;
            *(float *)(anim + 0x8) = f;
            switch (*(signed char *)(w + 0x364)) {
            case 3: {
                void (*fn)(unsigned char *);
                ret = 1;
                fn = *(void (**)(unsigned char *))(*(char **)(list + 0x14) + 0x68);
                if (fn != 0)
                    fn(obj);
                break;
            }
            case 4:
                *(signed char *)(w + 0x364) = 2;
                break;
            default:
                func_00088258(obj);
                break;
            }
        }
        break;
    }
    link = *(int **)(w + 0x348);
    if (link != 0)
        *link = *(int *)(anim + 0x20);
    return ret;
}
