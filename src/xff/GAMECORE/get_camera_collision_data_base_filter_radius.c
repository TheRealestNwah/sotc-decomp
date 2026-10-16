float get_camera_collision_data_base_filter_radius(float r, float a, float b)
{
    if (a < b)
        a = b;
    a += 0.1f;
    if (r < a)
        r = a;
    return r;
}
