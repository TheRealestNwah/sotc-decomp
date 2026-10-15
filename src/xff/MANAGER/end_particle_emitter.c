extern char *get_particle_emitter_from_emitter_id(int);

int end_particle_emitter(int a, int id, int immediate)
{
    char *e = get_particle_emitter_from_emitter_id(id);
    if (e == 0)
        return 0;
    *(int *)(e + 0x114) = 1;
    if (immediate == 1)
        *(int *)(e + 0xC4) = 0;
    return 1;
}
