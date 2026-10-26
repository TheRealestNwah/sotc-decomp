extern int get_main_particle_effect_lod_from_sheet(void *sheet);

int get_particle_camera_follow_attr_from_effect_id(void *sheet)
{
    if (sheet != 0) {
        return *(int *)((char *)get_main_particle_effect_lod_from_sheet(sheet) + 0xBC);
    }
    return -1;
}
