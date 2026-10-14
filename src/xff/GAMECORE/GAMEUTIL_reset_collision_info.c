typedef int s128 __attribute__((mode(TI)));
typedef unsigned int u128 __attribute__((mode(TI)));
extern void ConstructorCollisionDynamics(int);
extern s128 ZeroPoint;
extern s128 ZeroVector;

void GAMEUTIL_reset_collision_info(void *arg0)
{
    (*(int *)((char *)(arg0) + 0)) = 0;
    ConstructorCollisionDynamics(arg0 + 0x10);
    (*(s128 *)((char *)(arg0) + 0x40)) = (s128) ZeroPoint;
    (*(s128 *)((char *)(arg0) + 0x50)) = (s128) ZeroVector;
}
