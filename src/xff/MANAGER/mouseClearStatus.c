typedef struct {
    char pad0[8];
    float x;
    float y;
    float z;
    int dx;
    int dy;
    int wheel;
    int press[3];
    int release[3];
    int hold[3];
} MouseStatus;

void mouseClearStatus(MouseStatus *m)
{
    m->release[0] = m->release[1] = m->release[2] = m->press[0] = m->press[1] = m->press[2] = m->hold[0] = m->hold[1] = m->hold[2] = m->dx = m->dy = 0;
    m->x = m->y = m->z = 0.0f;
    m->wheel = 0;
}
