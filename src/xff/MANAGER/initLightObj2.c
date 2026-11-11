/* Parked: 56 diffs. Struct-by-value argument; the original copies the 0xB0-byte local straight into the argument area (no separate copy local) and stores the fields in a different order. File is initLightObj2.c because InitLightObj.c already exists (case-insensitive file names). */
typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;
typedef struct {
    char prefix[0x7C];
    int kind;
    Vec4 first;
    Vec4 second;
    float param0;
    float param1;
} LightDefinition;

extern char RO_0013FD30[];
extern void CreateLightObj(void *, int, LightDefinition);
extern void *memset(void *, int, unsigned int);

#ifdef NONMATCHING
void initLightObj(void *heap, int *a, int *b)
{
    LightDefinition e;
    LightDefinition d;
    char *p = (char *)&d;

    memset(p, 0, 0x7C);
    *(char **)(p + 0x00) = RO_0013FD30;
    *(int *)(p + 0x04) = 1;
    *(int *)(p + 0x4C) = b[5];
    *(float *)(p + 0x50) = ((float *)b)[6];
    *(int *)(p + 0x54) = b[9];
    d.kind = a[1];
    d.first.f[0] = ((float *)a)[2];
    d.first.f[1] = ((float *)a)[3];
    d.first.f[2] = ((float *)a)[4];
    d.first.f[3] = 0;
    d.second.f[0] = ((float *)a)[5];
    d.second.f[1] = ((float *)a)[6];
    d.second.f[2] = ((float *)a)[7];
    d.param0 = ((float *)a)[8];
    d.param1 = ((float *)a)[9];
    d.second.f[3] = 0;
    e = d;
    CreateLightObj(heap, 0x10, e);
}
#else
extern void initLightObj(void *, int *, int *);
#endif
