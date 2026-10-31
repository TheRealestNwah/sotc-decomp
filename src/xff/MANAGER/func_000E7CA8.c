typedef struct {
    int pad0;
    int active;
    char pad8[0x3C - 0x8];
    int id;
} CamWork;

extern void *memset(void *, int, unsigned int);
extern int GetLayoutObjWorkSize(CamWork *);
extern char *dynamic_cast_to_camera_obj(void *);
extern void isysFlushISYSLetterObj(void *);
extern void check_free_clip_screen(void *);
extern void check_free_transform_matrix_set(void *);

static int func_000E7CA8(CamWork *w)
{
    memset(w, 0, 0x7C);
    w->active = 1;
    w->id = -1;
    return GetLayoutObjWorkSize(w);
}

static void T_000E7CE8(void *obj)
{
    char *cam = dynamic_cast_to_camera_obj(obj);

    if (cam) {
        isysFlushISYSLetterObj(cam);
        check_free_clip_screen(cam + 0x250);
        check_free_transform_matrix_set(cam + 0x254);
    }
}
