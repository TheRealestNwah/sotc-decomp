typedef struct {
    float cursor_x;
    float cursor_y;
    float x;
    float y;
    float z;
    int dx;
    int dy;
    int wheel;
    int press[3];
    int release[3];
    int hold[3];
    float time[3];
    int prev;
} MouseStatus;

static inline void clear_mouse_status(MouseStatus *m)
{
    m->release[0] = m->release[1] = m->release[2] = m->press[0] = m->press[1] = m->press[2] = m->hold[0] = m->hold[1] = m->hold[2] = m->dx = m->dy = 0;
    m->x = m->y = m->z = 0.0f;
    m->wheel = 0;
}

extern MouseStatus B_0014DBB8;
extern int getDrawScreenWidth(void);
extern int getDrawScreenHeight(void);

void mouseGetStatus(MouseStatus *out)
{

    float cx, cy, ox, oy;

    B_0014DBB8.cursor_x += (float)(int)B_0014DBB8.x;
    B_0014DBB8.cursor_y += (float)(int)B_0014DBB8.y;
    cx = B_0014DBB8.cursor_x;
    if ((float)(getDrawScreenWidth() >> 1) < B_0014DBB8.cursor_x)
        ox = cx - (float)(getDrawScreenWidth() >> 1);
    else if (B_0014DBB8.cursor_x < -(float)(getDrawScreenWidth() >> 1))
        ox = cx + (float)(getDrawScreenWidth() >> 1);
    else
        ox = cx - B_0014DBB8.cursor_x;
    cy = B_0014DBB8.cursor_y;
    if ((float)(getDrawScreenHeight() >> 1) < B_0014DBB8.cursor_y)
        oy = cy - (float)(getDrawScreenHeight() >> 1);
    else if (B_0014DBB8.cursor_y < -(float)(getDrawScreenHeight() >> 1))
        oy = cy + (float)(getDrawScreenHeight() >> 1);
    else
        oy = cy - B_0014DBB8.cursor_y;
    B_0014DBB8.cursor_x -= ox;
    B_0014DBB8.cursor_y -= oy;
    B_0014DBB8.x -= ox;
    B_0014DBB8.y -= oy;
    *out = B_0014DBB8;
    clear_mouse_status(&B_0014DBB8);
}
