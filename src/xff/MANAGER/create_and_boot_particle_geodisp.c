extern void *get_fast_get_malloc_partition(void);
extern char *initParticleObject(void *, int);
extern char *GetGeoDispClass(unsigned char *);
extern void *func_000C58E0(void *, void *, void *, int, int, int);

char *create_and_boot_particle_geodisp(void *resource, void *geometry,
                                     int lower_mode, int upper_mode, int end_mode)
{
    char *object = initParticleObject(get_fast_get_malloc_partition(), 0x1F3);
    if (object != 0) {
        char *display = GetGeoDispClass((unsigned char *)object);
        *(void **)(display + 0xE8) = func_000C58E0(*(void **)object, resource,
                                                geometry, lower_mode,
                                                upper_mode, end_mode);
    }
    return object;
}
