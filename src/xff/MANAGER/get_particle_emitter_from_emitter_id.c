char *get_particle_emitter_from_emitter_id(char *p)
{
    if (p != 0) {
        return p + 0x10;
    }
    return 0;
}
