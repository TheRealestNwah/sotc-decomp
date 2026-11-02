typedef struct {
    float r, g, b;
    float pad0C;
    float near0, far0, max0;
    float pad1C;
    float near1, far1, max1;
} FogParam;

typedef struct {
    char pad00[0x4E];
    unsigned char r, g, b;
    char pad51[0x58 - 0x51];
    float near0, far0, max0;
    float near1, far1, max1;
} FogObj;

void UpdateFogCol(FogObj *o, FogParam *p)
{
    o->r = (unsigned int)p->r;
    o->g = (unsigned int)p->g;
    o->b = (unsigned int)p->b;
    o->near0 = p->near0;
    o->far0 = p->far0;
    o->max0 = p->max0;
    o->near1 = p->near1;
    o->far1 = p->far1;
    o->max1 = p->max1;
}
