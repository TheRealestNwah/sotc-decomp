typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;
typedef struct {
    Vec4 direction;
    Vec4 position;
    Vec4 velocity;
    Vec4 target;
    float parameter;
} WormDynamics;
extern Vec4 ZeroVector;
void ReflectIK_initWormDynamics(WormDynamics *work, Vec4 *position, Vec4 *direction, Vec4 *target, float parameter)
{
    work->position.q = position->q;
    work->velocity.q = ZeroVector.q;
    work->direction.q = direction->q;
    work->target.q = target->q;
    work->parameter = parameter;
}
