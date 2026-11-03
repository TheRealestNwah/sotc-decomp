#ifdef NONMATCHING /* near-miss: register allocation / scheduling differences remain */
typedef struct {
    int type;
    float dir[3];
    float col[3];
} LightParamEntry;

typedef struct {
    char pad0[0x34];
    float ambient;
    LightParamEntry light[4];
} LightParam;

extern float D_00135B50;
extern float D_00135B60[4];
extern float D_00135B70[4];
extern float D_00135B80[4];
extern float D_00135BA0[4];
extern float D_00135BB0[4];
extern float D_00135BC0[4];
extern float D_00135BD0[4];
extern int D_00135BE0[4];

extern void func_00016710(void);

void setLightParam(LightParam *p)
{
    D_00135BE0[0] = p->light[0].type;
    D_00135BA0[0] = p->light[0].dir[0];
    D_00135BA0[1] = p->light[0].dir[1];
    D_00135BA0[2] = p->light[0].dir[2];
    D_00135BA0[3] = 1.0f;
    D_00135B60[0] = p->light[0].col[0];
    D_00135B60[1] = p->light[0].col[1];
    D_00135B60[2] = p->light[0].col[2];
    D_00135B60[3] = 1.0f;
    D_00135BE0[1] = p->light[1].type;
    D_00135BB0[0] = p->light[1].dir[0];
    D_00135BB0[1] = p->light[1].dir[1];
    D_00135BB0[2] = p->light[1].dir[2];
    D_00135BB0[3] = 1.0f;
    D_00135B70[0] = p->light[1].col[0];
    D_00135B70[1] = p->light[1].col[1];
    D_00135B70[2] = p->light[1].col[2];
    D_00135B70[3] = 1.0f;
    D_00135BE0[2] = p->light[2].type;
    D_00135BC0[0] = p->light[2].dir[0];
    D_00135BC0[1] = p->light[2].dir[1];
    D_00135BC0[2] = p->light[2].dir[2];
    D_00135BC0[3] = 1.0f;
    D_00135B80[0] = p->light[2].col[0];
    D_00135B80[1] = p->light[2].col[1];
    D_00135B80[2] = p->light[2].col[2];
    D_00135B80[3] = 1.0f;
    D_00135BE0[3] = p->light[3].type;
    D_00135BD0[0] = p->light[3].dir[0];
    D_00135BD0[1] = p->light[3].dir[1];
    D_00135BD0[2] = p->light[3].dir[2];
    D_00135BD0[3] = 1.0f;
    D_00135B50 = p->ambient;
    func_00016710();
}
#endif
