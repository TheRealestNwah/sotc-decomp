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
} MouseStatus;

static inline void clear_mouse_status(MouseStatus *m)
{
    m->release[0] = m->release[1] = m->release[2] = m->press[0] = m->press[1] = m->press[2] = m->hold[0] = m->hold[1] = m->hold[2] = m->dx = m->dy = 0;
    m->x = m->y = m->z = 0.0f;
    m->wheel = 0;
}

extern MouseStatus B_0014DBB8;
extern void func_000CF510(void *);
extern void usbdevAddCallbackFunc(void (*)(void *), int);
extern int getDrawScreenWidth(void);
extern int getDrawScreenHeight(void);

void mouseInit(void)
{
    usbdevAddCallbackFunc(func_000CF510, 0);
    B_0014DBB8.cursor_x = (float)(8 - (getDrawScreenWidth() >> 1));
    B_0014DBB8.cursor_y = (float)(8 - (getDrawScreenHeight() >> 1));
    clear_mouse_status(&B_0014DBB8);
}
