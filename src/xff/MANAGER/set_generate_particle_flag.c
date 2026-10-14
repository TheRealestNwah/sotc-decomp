extern char *get_particle_emitter_from_emitter_id(int);

int set_generate_particle_flag(int a, int id, int flag)
{
    char *e = get_particle_emitter_from_emitter_id(id);
    if (e == 0)
        return 0;
    *(int *)(e + 0x168) = flag;
    return 1;
}
