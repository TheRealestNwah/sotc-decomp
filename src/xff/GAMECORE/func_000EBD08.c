extern void *get_cur_camera_target(void *);
extern void *GetCharacterClass(void *);
extern int is_camera_target_change(void *);

static int func_000EBD08(void *cam)
{
    void *t = get_cur_camera_target(cam);
    int r;

    if (t != 0 && GetCharacterClass(t) != 0)
        r = 1;
    else
        r = 0;
    return r;
}

static void func_000EBD48(char *c, void *o)
{
    if (is_camera_target_change(o) == 1)
        *(int *)(c + 0x2C40) = 5;
}
