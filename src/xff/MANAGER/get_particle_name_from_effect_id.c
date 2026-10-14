int get_particle_name_from_effect_id(char *p)
{
    if (p == 0) {
        return 0;
    }
    return *(int *)(p + 0x24);
}
