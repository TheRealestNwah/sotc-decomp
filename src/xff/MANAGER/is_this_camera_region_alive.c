extern void *B_0015E350[50];
extern int D_00139F44;
extern void **D_00139F48;
extern int get_manage_object_id_camera_region(void *);
extern int is_have_region_camera_region(void *);

void *is_this_camera_region_alive(void *region, int id)
{
    int i;

    if (region != 0) {
        for (i = 0; i < 50; i++) {
            if (region == B_0015E350[i]) {
                if (is_have_region_camera_region(B_0015E350[i]) == 1)
                    return B_0015E350[i];
                return 0;
            }
        }
        for (i = 0; i < D_00139F44; i++) {
            if (region == D_00139F48[i])
                return region;
        }
        if (id != -1) {
            for (i = 0; i < 50; i++) {
                if (id == get_manage_object_id_camera_region(B_0015E350[i])) {
                    if (is_have_region_camera_region(B_0015E350[i]) == 1)
                        return B_0015E350[i];
                    return 0;
                }
            }
            for (i = 0; i < D_00139F44; i++) {
                if (id == get_manage_object_id_camera_region(D_00139F48[i]))
                    return D_00139F48[i];
            }
        }
    }
    return 0;
}
