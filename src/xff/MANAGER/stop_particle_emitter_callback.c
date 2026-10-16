extern char *get_particle_emitter_from_emitter_id(int);

int stop_particle_emitter_callback(void *a, int id)
{
    char *e = get_particle_emitter_from_emitter_id(id);

    if (e == 0)
        return 0;
    *(int *)(e + 0x158) = 0;
    return 1;
}
