extern void *get_main_particle_effect_lod_from_sheet();

int get_particle_camera_follow_attr_from_effect_id(int arg0)
{
    if (arg0 != 0) {
        return (*(int *)((char *)(get_main_particle_effect_lod_from_sheet()) + 0xBC));
    }
    return -1;
}
