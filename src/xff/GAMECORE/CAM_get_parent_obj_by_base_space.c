extern void *get_cur_camera_target(void *);
extern void *GAMEUTIL_get_boss_obj(void);
extern void *getBossCloudObj(void);
extern void *GAMEUTIL_get_obj_from_stagelayout_sheet(void *);

void *CAM_get_parent_obj_by_base_space(int type, void *sheet, void *obj, void *cam)
{
    void *o;

    if (type == 1)
        return 0;
    if (type == 2 || type == 8)
        return get_cur_camera_target(cam);
    if (type == 3)
        return GAMEUTIL_get_boss_obj();
    if (type == 4)
        return getBossCloudObj();
    if (type == 7) {
        o = GAMEUTIL_get_boss_obj();
        if (o != 0)
            return o;
        return getBossCloudObj();
    }
    if (type == 5)
        return GAMEUTIL_get_obj_from_stagelayout_sheet(sheet);
    if (type == 6)
        return obj;
    return 0;
}
