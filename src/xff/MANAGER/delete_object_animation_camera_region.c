typedef struct { char pad[0x10]; void *obj; } Region;
extern Region *B_0015E350[];
extern void check_free_camera_region(Region **, void *);

int delete_object_animation_camera_region(void *obj)
{
    int i;
    if (obj != 0) {
        for (i = 0; i < 50; i++) {
            if (B_0015E350[i] != 0 && B_0015E350[i]->obj == obj) {
                check_free_camera_region(&B_0015E350[i], obj);
                return 1;
            }
        }
    }
    return 0;
}
