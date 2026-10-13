int get_particle_effect_from_lod(void *arg0, int arg1)
{
    return (*(int *)((char *)(arg0) + 0xD4)) + (arg1 * 0x1BC);
}
