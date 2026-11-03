typedef struct { float x, y, z, w; } Vec4;
typedef union { int i; float f; } IF;
typedef struct LightParam {
    char pad0[0x34];
    float amb;
    IF col0;
    float d0[3];
    float p0[3];
    IF col1;
    float d1[3];
    float p1[3];
    IF col2;
    float d2[3];
    float p2[3];
    IF col3;
    float d3[3];
} LightParam;
extern float D_00135B50;
extern Vec4 D_00135B60, D_00135B70, D_00135B80;
extern Vec4 D_00135BA0, D_00135BB0, D_00135BC0, D_00135BD0;
extern IF D_00135BE0[4];
extern void func_00016710(void);

void setLightParam(LightParam *p)
{
    Vec4 *d0 = &D_00135BA0, *p0 = &D_00135B60, *d1 = &D_00135BB0, *p1 = &D_00135B70;
    Vec4 *d2 = &D_00135BC0, *p2 = &D_00135B80, *d3 = &D_00135BD0;
    IF *c = D_00135BE0;
    c[0] = p->col0;
    d0->x = p->d0[0]; d0->y = p->d0[1]; d0->z = p->d0[2]; d0->w = 1.0f;
    p0->x = p->p0[0]; p0->y = p->p0[1]; p0->z = p->p0[2]; p0->w = 1.0f;
    c[1] = p->col1;
    d1->x = p->d1[0]; d1->y = p->d1[1]; d1->z = p->d1[2]; d1->w = 1.0f;
    p1->x = p->p1[0]; p1->y = p->p1[1]; p1->z = p->p1[2]; p1->w = 1.0f;
    c[2] = p->col2;
    d2->x = p->d2[0]; d2->y = p->d2[1]; d2->z = p->d2[2]; d2->w = 1.0f;
    p2->x = p->p2[0]; p2->y = p->p2[1]; p2->z = p->p2[2]; p2->w = 1.0f;
    c[3] = p->col3;
    d3->x = p->d3[0]; d3->y = p->d3[1]; d3->z = p->d3[2]; d3->w = 1.0f;
    D_00135B50 = p->amb;
    func_00016710();
}
