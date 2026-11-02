typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; void *p[4]; } Vec4;

typedef struct {
    char pad0[0x180];
    float unk180;
} GlobalVar;

extern GlobalVar gcGlobalVar;
extern void *isysGetThisSubThread(void);
extern char *GetLayoutClass(void *);
extern void *get_main_cameraman(void);
extern int is_disp_game_camera_model_ok(void);
extern int is_game_camera_mode_now(void *);
extern float *get_game_camera_WV_matrix(void *);
extern void iosInverseMatrix(float *, float *);
extern void GetQuaternionFromMatrix(void *, float *);
extern void UpdateLayoutClassPastSimpleGeometry(char *);
extern void UpdateLayoutClassSimpleGeometry(char *, float);
extern void scrRun(void);

void doit_game_camera_model(void)
{
    char *layout;
    void *cameraman;
    float matrix[16];

    for (;;) {
        layout = GetLayoutClass(isysGetThisSubThread());
        cameraman = get_main_cameraman();
        if (is_disp_game_camera_model_ok() == 1 && is_game_camera_mode_now(cameraman) == 0) {
            *(long long *)(*(char **)(layout + 0x144) + 0x260) &= ~0x400;
        } else {
            *(long long *)(*(char **)(layout + 0x144) + 0x260) |= 0x400;
        }
        iosInverseMatrix(matrix, get_game_camera_WV_matrix(cameraman));
        (*(Vec4 **)(layout + 0x134))->q = ((Vec4 *)&matrix[12])->q;
        GetQuaternionFromMatrix(*(void **)(layout + 0x13C), matrix);
        UpdateLayoutClassPastSimpleGeometry(layout);
        UpdateLayoutClassSimpleGeometry(layout, gcGlobalVar.unk180);
        scrRun();
    }
}
