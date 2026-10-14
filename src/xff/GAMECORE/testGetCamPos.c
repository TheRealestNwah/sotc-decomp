typedef int s128 __attribute__((mode(TI)));

typedef struct {
    s128 q;
} Vec4;

typedef struct {
    char pad0[0x134];
    Vec4 *pos;
    char pad138[0x20];
    void *matrix;
} LayoutClass;

extern LayoutClass *GetLayoutClass(void *);
extern void *get_main_cameraman_camera_obj(void);
extern void iosCopyMatrix(void *, void *);
extern Vec4 ZeroVector;

void *testGetCamPos(Vec4 *pos, void *matrix)
{
    void *camera = get_main_cameraman_camera_obj();

    if (camera != 0) {
        LayoutClass *layout = GetLayoutClass(camera);

        iosCopyMatrix(matrix, layout->matrix);
        *pos = *layout->pos;
    } else {
        *pos = ZeroVector;
    }
    return camera;
}
