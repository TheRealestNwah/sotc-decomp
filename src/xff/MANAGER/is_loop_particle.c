extern void *func_000C54B0(int effect);
extern int get_main_particle_effect_lod_from_sheet(void *sheet);
extern int get_top_particle_effect_from_lod(void *lod);

int is_loop_particle(int effect)
{
    if (effect != 0) {
        void *sheet = func_000C54B0(effect);
        void *lod = (void *)get_main_particle_effect_lod_from_sheet(sheet);
        char *particle = (char *)get_top_particle_effect_from_lod(lod);
        return *(int *)(particle + 0x10) == 1;
    }
    return 0;
}
