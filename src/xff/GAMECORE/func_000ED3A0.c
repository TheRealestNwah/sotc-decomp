extern void boot_camera_lws_animation_by_script(void *);
extern void *get_main_type_camera_lws_animation(void);

static int func_000ED3A0(char *c)
{
    void *cur = *(void **)(c + 0x90);
    int r = 0;

    if (cur == 0) {
        void *anim = *(void **)(c + 0xF8);

        if (anim != 0) {
            boot_camera_lws_animation_by_script(anim);
            *(void **)(c + 0x90) = get_main_type_camera_lws_animation();
            return 1;
        }
    }
    return r;
}
