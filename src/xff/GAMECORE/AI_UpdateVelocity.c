typedef struct {
    char pad0[0x190];
    float delta;
} GlobalVar;

extern GlobalVar gcGlobalVar;

int AI_UpdateVelocity(float *vel, float target, float accel)
{
    float v = *vel;
    int moving = 1;

    if (v < target) {
        v += accel * gcGlobalVar.delta;
        if (target < v) {
            v = target;
            moving = 0;
        }
    } else {
        v -= accel * gcGlobalVar.delta;
        if (v < target) {
            v = target;
            moving = 0;
        }
    }
    *vel = v;
    return moving;
}
