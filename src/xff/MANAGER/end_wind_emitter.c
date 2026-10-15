extern char *B_00149AB0[];

static inline int is_valid_emitter_id(unsigned int i)
{
    return i < 80;
}

int end_wind_emitter(unsigned int i)
{
    char *e = is_valid_emitter_id(i) == 1 ? B_00149AB0[i] : 0;
    if (e != 0) {
        *(int *)(e + 0xA0) = 0;
        return 1;
    }
    return 0;
}
