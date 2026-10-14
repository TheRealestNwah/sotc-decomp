extern int _optionWorkChk(int);
extern int getDrawScreenHeight(void);
extern int getDrawScreenWidth(void);
extern void * get_camera_obj(void *);
extern int get_main_cameraman(void);
extern int set_camera_obj_screen_size(char *, int, int);
extern void set_screen_wide_and_progressive(int, int);
extern void update_camera_obj(void *);

#define NULL ((void *)0)
void setAspect(void) {
    int temp_s0;
    int temp_s0_2;
    int temp_v0;
    signed char *temp_v0_2;

    temp_s0 = _optionWorkChk(2);
    set_screen_wide_and_progressive(temp_s0, _optionWorkChk(6));
    temp_v0 = get_main_cameraman();
    if (temp_v0 != 0) {
        temp_v0_2 = get_camera_obj((void *) temp_v0);
        if (temp_v0_2 != NULL) {
            temp_s0_2 = getDrawScreenWidth();
            set_camera_obj_screen_size(temp_v0_2, temp_s0_2, getDrawScreenHeight());
            update_camera_obj(temp_v0_2);
        }
    }
}
