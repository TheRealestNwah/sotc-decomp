typedef struct {
    char pad0[0xC];
    int (*fn)(void *, void *);
    int x10;
} ClothCB;

extern char *GetLayoutClass(void *);
extern void *GetGeometryPointerObject(void *);
extern void GetLayoutClassWindGeometry(void *, void *);
extern char ZeroVector[];
extern void GetClothDynamics(void *, float, float, int, void *);
extern void ResetClothDynamics(void *);

static inline void *GetCharacterClass(void *character)
{
    char *obj = character;

    switch ((unsigned char)obj[8]) {
    case 9:
        return obj + 0x90;
    case 0x16:
        return obj + 0x90;
    default:
        return 0;
    }
}

void getClothGeometry(void *cloth, char *obj, float a, float b)
{
    char *lay = GetLayoutClass(cloth);
    char *chr;
    signed char *flag;
    char *o;
    char *c2;
    ClothCB *cb;
    void *p;
    int n;
    int mode;

    if (*(int *)(lay + 0x180) == 0)
        return;
    chr = GetCharacterClass(obj);
    if (*(signed char *)(chr + 0x53C) != 0)
        return;
    if (cloth == obj && *(int *)(lay + 0x124) != 0) {
        o = GetGeometryPointerObject(lay + 0xC0);
        if (o != 0) {
            c2 = GetCharacterClass(o);
            if (c2 != 0 && (c2[0x52A] & 0x7F))
                chr[0x52A] = c2[0x52A] & 0x7F;
        }
    }
    flag = (signed char *)(chr + 0x52A);
    if (*flag != 0) {
        __asm__ volatile("sq $0, 0(%0)" : : "r"(lay + 0x30) : "memory");
        GetLayoutClassWindGeometry(lay, ZeroVector);
        GetClothDynamics(cloth, a, b, 1, 0);
        ResetClothDynamics(cloth);
        n = *flag & 0x7F;
        while (n-- != 0)
            GetClothDynamics(cloth, a, b, 1, 0);
        *flag |= 0x80;
    }
    cb = *(ClothCB **)(lay + 0x178);
    p = (void *)(*(int *)(chr + 0xE38) + *(short *)(chr + 0x370) * 4);
    mode = 2;
    if (cb->x10 == 0) {
        if (cb->fn != 0)
            mode = cb->fn(obj, p) != 0;
        else
            mode = *(signed char *)(chr + 0x362) == 0;
    }
    GetClothDynamics(cloth, a, b, mode, p);
}
