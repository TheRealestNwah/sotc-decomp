typedef int s128 __attribute__((mode(TI)));

extern int GetSkeletonFocusNode(void *);
extern void *CAM_get_target_obj(void *);
extern int get_place_status_camera_place_status(void *);
extern void *get_manage_obj_camera_place_status(void *);
extern void *GAMEUTIL_get_parent_object(void *);
extern void *GAMEUTIL_get_boss_obj(void);
extern int GAMEUTIL_get_node_posi_by_id(s128 *, void *, int);

static int func_000D6A98(s128 *out, int id, void *skel, char *cam)
{
    char *place;
    void *obj;
    int node;

    if (id == 0x69) {
        *out = *(s128 *)(cam + 0x70);
        return 1;
    }
    place = cam + 0x1270;
    node = GetSkeletonFocusNode(skel);
    obj = 0;
    switch (id) {
    case 100:
        break;
    case 101:
        obj = CAM_get_target_obj(cam + 0x23C);
        break;
    case 102:
        if (get_place_status_camera_place_status(place) == 2) {
            obj = get_manage_obj_camera_place_status(place);
        } else {
            obj = GAMEUTIL_get_parent_object(CAM_get_target_obj(cam + 0x23C));
        }
        break;
    case 103:
        obj = get_manage_obj_camera_place_status(place);
        break;
    case 104:
        obj = GAMEUTIL_get_boss_obj();
        break;
    case 105:
        break;
    }
    return GAMEUTIL_get_node_posi_by_id(out, obj, node);
}
