typedef struct {
    int active;
    float scale_x;
    float scale_y;
    float power;
    float time;
} AttackEffect;

extern AttackEffect B_0019CD28;
extern unsigned char gcGlobalVar[];

void startAttackEffect(float power)
{
    AttackEffect *e = &B_0019CD28;

    e->active = 1;
    e->scale_x = 0.5f;
    e->scale_y = 0.5f;
    e->time = *(float *)(gcGlobalVar + 0x178);
    e->power = power;
}
