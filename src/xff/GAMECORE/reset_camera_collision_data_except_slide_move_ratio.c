extern int ConstructorCollisionDynamics();

int reset_camera_collision_data_except_slide_move_ratio(int *p)
{
    p[0] = 0;
    p[1] = 0;
    p[2] = 0;
    p[3] = 0;
    return ConstructorCollisionDynamics(p + 4);
}
