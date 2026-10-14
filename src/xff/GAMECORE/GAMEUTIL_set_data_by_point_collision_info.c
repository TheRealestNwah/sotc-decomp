typedef int s128 __attribute__((mode(TI)));
extern void ConvertFromCollisionPointToDynamics(s128 *, void *);
extern void GAMEUTIL_set_data_by_dynamics_collision_info(void *, s128 *, int);
void GAMEUTIL_set_data_by_point_collision_info(void *out, void *point)
{
    s128 dynamics[3];
    ConvertFromCollisionPointToDynamics(dynamics, point);
    GAMEUTIL_set_data_by_dynamics_collision_info(out, dynamics, 0);
}
