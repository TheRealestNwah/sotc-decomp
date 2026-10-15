extern char *B_00149AB0[];

static inline int is_valid_emitter_id(unsigned int i)
{
    return i < 80;
}

int stop_wind_emitter_callback(unsigned int i)
{
    char *e = is_valid_emitter_id(i) == 1 ? B_00149AB0[i] : 0;
    if (e != 0) {
        *(int *)(e + 0xF0) = 0;
        return 1;
    }
    return 0;
}
