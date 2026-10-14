extern void *get_cur_camera_target(void *);
extern void *GetCharacterClass(void *);
int is_proper_camera_target_game_camera(void *camera)
{
    void *target=get_cur_camera_target(camera);
    if (!target) goto no;
    if (!GetCharacterClass(target)) goto no;
    return 1;
no:
    return 0;
}
