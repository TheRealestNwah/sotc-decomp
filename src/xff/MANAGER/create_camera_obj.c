typedef struct {
    float x, y, z, w;
} __attribute__((aligned(16))) Vec4;

extern void *memset(void *, int, unsigned int);
extern int func_000E7CA8(void *);
extern char D_000E7CE8[];
extern char *_isysCreateObj(void *, int, int, int, void *, int);
extern void isysInitISYSLetterObj(void *);
extern void InitLayoutObj(void *, void *);
extern void set_camera_position(void *, Vec4 *);
extern void set_camera_direction(void *, Vec4 *);
extern void set_camera_up_direction(void *, Vec4 *);
extern int create_clip_screen(void *, void *, void *, float);
extern int create_transform_matrix_set(void *);
extern void update_camera_obj(void *);

char *create_camera_obj(void *sys, void *a1, void *a2, float f)
{
    Vec4 pos;
    Vec4 dir;
    Vec4 up;
    char layout[0x80];
    char *obj;

    memset(&pos, 0, 0x10);
    pos.w = 1.0f;
    memset(&dir, 0, 0x10);
    dir.z = 1.0f;
    memset(&up, 0, 0x10);
    up.y = 1.0f;
    obj = _isysCreateObj(sys, 0x11, 0x260, func_000E7CA8(layout), D_000E7CE8, 0x10);
    isysInitISYSLetterObj(obj);
    InitLayoutObj(obj, layout);
    set_camera_position(obj, &pos);
    set_camera_direction(obj, &dir);
    set_camera_up_direction(obj, &up);
    *(int *)(obj + 0x250) = create_clip_screen(sys, a1, a2, f);
    *(int *)(obj + 0x254) = create_transform_matrix_set(sys);
    update_camera_obj(obj);
    return obj;
}
