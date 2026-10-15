typedef struct { int a; int b; int arr[5]; } CamMan;
extern CamMan B_0019FD20;
extern char B_0019FD40[];
extern void init_camera_lws_animation_manager(void);
extern void init_camera_region_manager(void);
extern void constructor_camera_context(void *);
extern void push_camera_context(void *);
extern void reset_camera_vs_ofst_cntrl_param_segment_array(void);

void init_cameraman_manager(void)
{
    int i;
    B_0019FD20.a = -1;
    B_0019FD20.b = 0;
    for (i = 4; i >= 0; i--)
        B_0019FD20.arr[i] = 0;
    init_camera_lws_animation_manager();
    init_camera_region_manager();
    constructor_camera_context(B_0019FD40);
    push_camera_context(B_0019FD40);
    reset_camera_vs_ofst_cntrl_param_segment_array();
}
