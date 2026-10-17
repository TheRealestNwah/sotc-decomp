typedef int s128 __attribute__((mode(TI)));

extern void *get_main_cameraman_camera_obj(void);
extern char *GetLayoutClass(unsigned char *);
extern void iosCopyMatrix(void *, void *);
extern s128 ZeroVector;

void *testGetCamPos(s128 *out, void *matrix)
{
    void *camera = get_main_cameraman_camera_obj();
    if (camera) {
        char *layout = GetLayoutClass(camera);
        iosCopyMatrix(matrix, *(void **)(layout + 0x158));
        *out = **(s128 **)(layout + 0x134);
    } else {
        *out = ZeroVector;
    }
    return camera;
}
