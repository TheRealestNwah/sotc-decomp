typedef int Qword __attribute__((mode(TI)));
typedef union Vector { Qword quad; float v[4]; } Vector;
typedef struct ClipScreen ClipScreen;

extern int get_camera_position(int);
extern int get_camera_direction(int);
extern int get_camera_up_direction(int);
extern void *get_clip_screen(void *);
extern float get_view_angle(ClipScreen *);

void get_camera_parameter_cameraman(Vector *position, Vector *direction, Vector *up,
                                    float *angle, void **manager)
{
    position->quad = ((Vector *)get_camera_position((int)*manager))->quad;
    direction->quad = ((Vector *)get_camera_direction((int)*manager))->quad;
    up->quad = ((Vector *)get_camera_up_direction((int)*manager))->quad;
    *angle = get_view_angle(get_clip_screen(*manager));
}
