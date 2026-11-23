typedef struct { int w[0x48 / 4]; } A48;
typedef struct { int w[0x194 / 4]; } A194;
typedef struct { int w[0xCC / 4]; } ACC;
typedef struct { int w[0x84 / 4]; } A84;
typedef struct { int w[0xD0 / 4]; } AD0;
typedef struct { int w[0xE4 / 4]; } AE4;
typedef struct { int w[0x8C / 4]; } A8C;
typedef struct {
    int head;
    A48 a;
    A194 b;
    ACC c;
    A84 d;
    AD0 e;
    AE4 f;
    AE4 g;
    A8C h;
} CamParam;

static void func_000ED678(CamParam *dst, CamParam *src)
{
    dst->head = src->head;
    dst->a = src->a;
    dst->b = src->b;
    dst->c = src->c;
    dst->d = src->d;
    dst->e = src->e;
    dst->f = src->f;
    dst->g = src->g;
    dst->h = src->h;
}
