/* Parked: 25 words off, only the scheduling of the argument loads differs; struct is copied through a second 8-aligned local. */
#ifdef NONMATCHING
typedef struct LightDesc {
    void *vtbl;
    int f4;
    char pad8[0x44];
    int f4C;
    float f50;
    int f54;
    char pad58[0x24];
    int f7C;
    float f80, f84, f88;
    int f8C;
    float f90, f94, f98;
    int f9C;
    float fA0, fA4;
    char padA8[8];
} LightDesc __attribute__((aligned(8)));

extern char RO_0013FD30[];
extern void *memset(void *, int, unsigned int);
extern void CreateLightObj(int, int, LightDesc);

void initLightObj(int arg0, int *arg1, int *arg2)
{
    LightDesc e, d;

    memset(&d, 0, 0x7C);
    d.vtbl = RO_0013FD30;
    d.f4 = 1;
    d.f4C = arg2[5];
    d.f50 = ((float *)arg2)[6];
    d.f54 = arg2[9];
    d.f7C = arg1[1];
    d.f80 = ((float *)arg1)[2];
    d.f84 = ((float *)arg1)[3];
    d.f88 = ((float *)arg1)[4];
    d.f8C = 0;
    d.f90 = ((float *)arg1)[5];
    d.f94 = ((float *)arg1)[6];
    d.f98 = ((float *)arg1)[7];
    d.f9C = 0;
    d.fA0 = ((float *)arg1)[8];
    d.fA4 = ((float *)arg1)[9];
    e = d;
    CreateLightObj(arg0, 0x10, e);
}
#else
extern void initLightObj(int, int *, int *);
#endif
