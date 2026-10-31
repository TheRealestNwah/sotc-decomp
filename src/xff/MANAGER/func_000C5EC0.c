extern float get_particle_lod_base_size(void *);

static void func_000C5EC0(char *o, char *p)
{
    float s;
    int cur;

    if (*(int *)(p + 0x8) == 0) {
        *(int *)(o + 0x118) = 0;
        return;
    }
    s = get_particle_lod_base_size(o);
    cur = *(int *)(o + 0x118);
    if (*(int *)(p + 0x8) == 1) {
        if (s < *(float *)(p + 0x14))
            *(int *)(o + 0x118) = 1;
        else if (s < *(float *)(p + 0x18))
            *(int *)(o + 0x118) = cur;
        else
            *(int *)(o + 0x118) = 0;
    } else {
        if (s < *(float *)(p + 0xC))
            *(int *)(o + 0x118) = 2;
        else if (s < *(float *)(p + 0x10))
            *(int *)(o + 0x118) = cur;
        else if (s < *(float *)(p + 0x14))
            *(int *)(o + 0x118) = 1;
        else if (s < *(float *)(p + 0x18))
            *(int *)(o + 0x118) = cur;
        else
            *(int *)(o + 0x118) = 0;
    }
}
