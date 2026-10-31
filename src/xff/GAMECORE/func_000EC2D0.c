extern char *GAMEUTIL_get_motion_kind(void *);
extern int GAMEUTIL_get_character_type(void *);
extern void GAMEUTIL_get_1p_left_analog_input(float *, float *);
extern int is_pass_camera_etc_condition(unsigned int, void *);

static void func_000EC2D0(int *type, int *kind, void *obj, char *cam)
{
    char *mk = GAMEUTIL_get_motion_kind(obj);
    float x;
    float y;
    int k;

    *type = GAMEUTIL_get_character_type(obj);
    if (mk != 0) {
        GAMEUTIL_get_1p_left_analog_input(&x, &y);
        k = *(int *)(mk + 0x90);
        *kind = k;
        switch (k) {
        case 9:
            if (!is_pass_camera_etc_condition(2, cam + 0x10))
                *kind = 0;
            break;
        case 0x1A:
            if (x <= 0.0f)
                *kind = 0x25;
            break;
        case 0x1B:
            if (0.0f <= x)
                *kind = 0x25;
            break;
        }
    } else {
        *kind = 0;
    }
}
