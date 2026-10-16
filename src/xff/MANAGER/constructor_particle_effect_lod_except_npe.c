extern void iosUnitMatrix(void *);

void constructor_particle_effect_lod_except_npe(char *p)
{
    *(int *)(p + 0xD0) = 0;
    *(int *)(p + 0xD4) = 0;
    *(int *)(p + 0xD8) = 0;
    *(int *)(p + 0xDC) = 0;
    iosUnitMatrix(p + 0xE0);
}
