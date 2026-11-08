extern char RO_00119A90[];
extern void *memset(void *, int, unsigned int);
extern void CreateLightObj(int, int, void *);

typedef struct {
    void *vt;
    int one;
    char pad8[0x44];
    int a4C;
    float a50;
    int a54;
    char pad58[0x24];
    int a7C;
    float a80;
    float a84;
    float a88;
    int a8C;
    float a90;
    float a94;
    float a98;
    int a9C;
    float aA0;
    float aA4;
    char padA8[8];
} __attribute__((aligned(8))) LightDesc;

#ifdef NONMATCHING
/* Parked: 22 words differ (load/store scheduling of the descriptor fields). */
void initLightObj(int obj, char *src, char *cfg)
{
    LightDesc dst;
    LightDesc tmp;

    memset(&tmp, 0, 0x7C);
    tmp.vt = RO_00119A90;
    tmp.one = 1;
    tmp.a4C = *(int *)(cfg + 0x14);
    tmp.a50 = *(float *)(cfg + 0x18);
    tmp.a54 = *(int *)(cfg + 0x24);
    tmp.a7C = *(int *)(src + 4);
    tmp.a80 = *(float *)(src + 8);
    tmp.a84 = *(float *)(src + 0xC);
    tmp.a88 = *(float *)(src + 0x10);
    tmp.a8C = 0;
    tmp.aA4 = *(float *)(src + 0x24);
    tmp.a90 = *(float *)(src + 0x14);
    tmp.a94 = *(float *)(src + 0x18);
    tmp.a98 = *(float *)(src + 0x1C);
    tmp.aA0 = *(float *)(src + 0x20);
    tmp.a9C = 0;
    dst = tmp;
    CreateLightObj(obj, 0x10, &dst);
}
#else
void initLightObj(int obj, char *src, char *cfg);
#endif
