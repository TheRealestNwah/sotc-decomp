extern int *B_00149AB0[];

static inline int is_valid_emitter_id(unsigned int i)
{
    return i < 80;
}

int stop_wind_emitter_geometry_pointer_reference(unsigned int i)
{
    int *e = is_valid_emitter_id(i) == 1 ? B_00149AB0[i] : 0;
    if (e != 0) {
        e[2] = 0;
        if (e[0] == 2)
            e[64] = 0;
        return 1;
    }
    return 0;
}
