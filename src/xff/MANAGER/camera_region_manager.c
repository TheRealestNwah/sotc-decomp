/* Camera region manager: the table of object-animation camera regions. */

typedef struct {
    int type;
    char pad4[0xC];
    void *unk10;
} CameraRegion;

extern CameraRegion *B_0015E350[50];
extern int D_00139F4C;
extern int D_00139F50;
extern int rootPtn;
extern void *memset(void *, int, unsigned int);
extern void doit_camera_region(CameraRegion *, void *, float);
extern CameraRegion *create_and_init_camera_region(int, void *, int, void *, void *, void *);
extern void check_free_camera_region(CameraRegion **);

void init_camera_region_manager(void)
{
    memset(B_0015E350, 0, sizeof(B_0015E350));
}

void doit_camera_region_manager(void *arg, float t)
{
    int i;
    for (i = 0; i < 50; i++) {
        if (B_0015E350[i] != 0) {
            doit_camera_region(B_0015E350[i], arg, t);
        }
    }
}

int add_object_animation_camera_region(void *obj, void *a1, void *a2)
{
    int i;
    if (obj != 0 && a1 != 0) {
        for (i = 0; i < 50; i++) {
            if (B_0015E350[i] == 0) {
                B_0015E350[i] = create_and_init_camera_region(0, a2, 0, obj, a1, &rootPtn);
                return 1;
            }
        }
    }
    return 0;
}

int delete_object_animation_camera_region(void *obj)
{
    int i;
    if (obj != 0) {
        for (i = 0; i < 50; i++) {
            if (B_0015E350[i] != 0 && B_0015E350[i]->unk10 == obj) {
                check_free_camera_region(&B_0015E350[i]);
                return 1;
            }
        }
    }
    return 0;
}

int get_max_object_animation_camera_region(void)
{
    return 50;
}

int get_cur_total_object_animation_camera_region(void)
{
    int i;
    int n = 0;
    for (i = 0; i < 50; i++) {
        if (B_0015E350[i] != 0) {
            n++;
        }
    }
    return n;
}

int *get_col_attr_cam_region_select_flag(void)
{
    return &D_00139F4C;
}

int *get_col_attr_cam_region_select_index(void)
{
    return &D_00139F50;
}
