extern int func_000C54B0();
extern int get_main_particle_effect_lod_from_sheet(int);
extern void *get_top_particle_effect_from_lod(int);

int is_loop_particle(int arg0)
{
    if (arg0 != 0) {
        return (*(int *)((char *)(get_top_particle_effect_from_lod(get_main_particle_effect_lod_from_sheet(func_000C54B0()))) + 0x10)) == 1;
    }
    return 0;
}
