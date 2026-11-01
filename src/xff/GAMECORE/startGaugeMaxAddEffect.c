typedef struct {
    int mode;
    float a;
    float b;
    int pad;
    float time;
} Effect;
extern char gcGlobalVar[];
extern Effect B_0019CD10;
extern void func_000BC988(int);

static inline void start_effect(float a, float b)
{
    do { func_000BC988(4); } while (0);
    B_0019CD10.mode = 1;
    B_0019CD10.time = *(float *)(gcGlobalVar + 0x178);
    B_0019CD10.b = b;
    B_0019CD10.a = a;
}
void startGaugeMaxAddEffect(void) { start_effect(8.0f, 0.5f); }
