extern void *GAMEUTIL_get_boss_obj(void);
extern char *GetScriptCharacterClass(void *);
int get_boss_subjective_camera_lws_animation_param(void)
{
    void *b = GAMEUTIL_get_boss_obj();
    if (b == 0)
        return 0;
    return *(int *)(GetScriptCharacterClass(b) + 0x11F4);
}
