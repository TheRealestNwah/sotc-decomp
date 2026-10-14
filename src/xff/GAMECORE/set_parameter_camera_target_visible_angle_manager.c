typedef struct {
    char pad0[0x3DC];
    int count;
    float angle;
    float fov;
    float step;
} VisibleAngleManager;

void set_parameter_camera_target_visible_angle_manager(VisibleAngleManager *m, int count, float degrees, float fov)
{
    m->count = count;
    if (count / 2 * 2 == count - 1) {
        m->count = count + 1;
    }
    if (m->count > 20) {
        m->count = 20;
    }
    m->fov = fov;
    m->angle = degrees * 0.0174532925f;
    m->step = m->angle / m->count;
}
